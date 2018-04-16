#include <cstdlib>
#include <cstring>
#include "endian.h"
#include "crc.h"
#include "decoder.hpp"

namespace OoT_Randomizer {

namespace Decoder {

#define INTSIZE 0x01000000    //16,777,216 bytes
#define COMPSIZE 0x02000000   //33,554,432 bytes
#define DECOMPSIZE 0x04000000 //67,108,864 bytes

static const thread_local uint32_t* inROM;
static thread_local uint32_t* outROM;
static const thread_local uint32_t* inTable;
static thread_local uint32_t* outTable;

typedef struct t_offsets
{
    uint32_t startV;   //Start Virtual Address
    uint32_t endV;     //End Virtual Address
    uint32_t startP;   //Start Physical Address
    uint32_t endP;     //End Phycical Address
}
Offsets;

static bool decode(uint8_t*, size_t, uint8_t*, size_t);
static bool findOffsets(uint32_t, Offsets *offsets);
static bool setOffsets(uint32_t, Offsets);
static uint32_t findTable();

bool loadAndDecodeFile(const std::vector<uint8_t> &in_buf, std::vector<uint8_t> &buf) {
    uint32_t tableOffset{0}, tableSize{0};
    Offsets offsets{0, 0, 0, 0}, curFile{0, 0, 0, 0};

    if ((reinterpret_cast<uintptr_t>(buf.data()) % alignof (uint32_t)) ||
        (reinterpret_cast<uintptr_t>(in_buf.data()) % alignof (uint32_t))) {
        return false;
    }
    if (in_buf.size() < COMPSIZE || buf.size() < DECOMPSIZE)
        abort();
    outROM = reinterpret_cast<uint32_t*>(buf.data());
    inROM = reinterpret_cast<const uint32_t*>(in_buf.data());

    //Find table offsets
    tableOffset = findTable();
    if (!~tableOffset) {
        return false;
    }
    if (tableOffset >= COMPSIZE) {
        abort();
    }
    if (tableOffset & (alignof (uint32_t) - 1)) {
        return false;
    }
    static_assert(alignof (uint32_t) <= 4, "uint32_t must have an alignment <= 4");
    static_assert(sizeof(uint32_t) == 4, "uint32_t must have size 4");
    static_assert(COMPSIZE == 2*INTSIZE, "COMPSIZE must be twice INTSIZE");
    static_assert(DECOMPSIZE == 4*INTSIZE, "DECOMPSIZE must be 4 times INTSIZE");
    static_assert(INTSIZE == (1UL << 24), "INTSIZE must equal (1 << 24)");
    inTable = inROM + (tableOffset >> 2);
    outTable = outROM + (tableOffset >> 2);
    if (!findOffsets(2, &offsets)) {
        return false;
    }

    if (offsets.endV < offsets.startV) {
        return false;
    }
    tableSize = offsets.endV - offsets.startV;

    //Change everything past the table in outROM to 0
    memset((uint8_t*)(outROM) + offsets.endV, 0, DECOMPSIZE - offsets.endV);

    for (uint32_t i = tableSize/16 - 1; i--;)
    {
        if (!findOffsets(i, &curFile)) {
            return false;
        }
        uint32_t size = curFile.endV - curFile.startV;

        //Don't do anything to this one for some reason.
        //Not sure why, but it breaks otherwise
        if(i != 2)
        {
            if (curFile.endV - curFile.startV) abort();
            if (curFile.startV >= COMPSIZE) return false;
            if (size > COMPSIZE - curFile.startV) return false;
            if (curFile.startP >= COMPSIZE) return false;
            if (size > COMPSIZE - curFile.startP) return false;
            //Copy if decoded, decode if encoded
            if(curFile.endP == 0x00000000)
                memcpy((char*)outROM + curFile.startV, (char*)inROM + curFile.startP, size);
            else
                decode((uint8_t*)inROM + curFile.startP, COMPSIZE, (uint8_t*)outROM + curFile.startV, size);

            //Clean up outROM's table
            curFile.startP = curFile.startV;
            curFile.endP = 0x00000000;
            if (!setOffsets(i, curFile)) {
                return false;
            }
        }
    }

    return true;
}

/*
        Function: findTable
        Description: Finds the table offset for the inROM (the encoded one)
        Paramaters: N/A (Uses some globals)
        Returns: Offset of table
*/
uint32_t findTable()
{
    uint32_t i = 0;

    while(i+4 < INTSIZE)
    {
        //Thsese values mark the begining of the file table
        if(be32toh(inROM[i]) == 0x7A656C64)
        {
            if(be32toh(inROM[i+1]) == 0x61407372)
            {
                if((be32toh(inROM[i+2]) & 0xFF000000) == 0x64000000)
                {
                    //Search for the begining of the filetable
                    while (be32toh(inROM[i]) != 0x00001060) {
                        if (i < INTSIZE - 1) {
                            i++;
                        } else {
                            return UINT32_MAX;
                        }
                    }
                    return((i-4) * sizeof(uint32_t));
                }
            }
        }

        i += 4;
    }
    return UINT32_MAX;
}

/*
        Function: findOffsets
        Description: Finds a given entry in the inTable array
        Paramaters: Number of the entry to find (Uses some globals)
        Returns: Offsets struct containing table info
*/
bool findOffsets(uint32_t i, Offsets *offsets)
{
    if (i > (INTSIZE >> 2) - 4) {
        return false;
    }

    //First 32 bytes are VROM start address, next 32 are VROM end address
    //Next 32 bytes are Physical start address, last 32 are Physical end address
    offsets->startV = be32toh(inTable[i*4]);
    offsets->endV   = be32toh(inTable[(i*4)+1]);
    offsets->startP = be32toh(inTable[(i*4)+2]);
    offsets->endP   = be32toh(inTable[(i*4)+3]);

    return offsets->startV <= offsets->endV && (offsets->startP <= offsets->endP || 0 == offsets->endP);
}

/*
        Function: setOffsets
        Description: Sets the table vales in outTable
        Paramaters: Number of the entry to set, Offset struct containing table info (Uses some globals)
        Returns: True if and only if the offsets were in range.
*/
bool setOffsets(uint32_t i, Offsets offsets)
{
    if ((INTSIZE >> 2) - 4 < i) { return false; }
    //First 32 bytes are VROM start address, next 32 are VROM end address
    //Next 32 bytes are Physical start address, last 32 are Physical end address
    outTable[i*4]     = htobe32(offsets.startV);
    outTable[(i*4)+1] = htobe32(offsets.endV);
    outTable[(i*4)+2] = htobe32(offsets.startP);
    outTable[(i*4)+3] = htobe32(offsets.endP);
    return true;
}

/*
        Function: decode
        Description: Decodes/decompresses portions of data using Yaz0 decoding
        Paramaters: Source array, Destination array, Size of decompressed data
        Returns: Whether the decoding was successful
*/
static bool decode(uint8_t* source, size_t compressed_size, uint8_t* decomp, size_t decompSize)
{
    uint32_t srcPlace = 0, dstPlace = 0;
    uint32_t dist, copyPlace, numBytes;
    uint8_t codeByte, byte1, byte2;
    uint8_t bitCount = 0;

    source += 0x10;
    while(dstPlace < decompSize && srcPlace < compressed_size)
    {
        //If there are no more bits to test, get a new byte
        if(!bitCount)
        {
            if (srcPlace >= compressed_size) {
                return false;
            }
            codeByte = source[srcPlace++];
            bitCount = 8;
        }


        //If bit 7 is a 1, just copy 1 byte from source to destination
        //Else do some decoding
        if(codeByte & 0x80)
        {
            if (dstPlace >= decompSize) return false;
            decomp[dstPlace++] = source[srcPlace++];
            continue;
        }
        else
        {
            if (srcPlace + 2 > compressed_size) {
                return false;
            }
            //Get 2 bytes from source
            byte1 = source[srcPlace++];
            byte2 = source[srcPlace++];

            //Calculate distance to move in destination
            //And the number of bytes to copy
            dist = ((byte1 & 0xF) << 8) | byte2;
            copyPlace = dstPlace - (dist + 1);
            numBytes = byte1 >> 4;

            //Do more calculations on the number of bytes to copy
            if(!numBytes) {
                if (srcPlace >= compressed_size)
                    return false;
                else
                    numBytes = source[srcPlace++] + 0x12;
            } else {
                numBytes += 2;
            }
            //Copy data from a previous point in destination
            //to current point in destination
            if (dstPlace >= decompSize) return false;
            if (decompSize - dstPlace > numBytes) return false;
            if (copyPlace >= decompSize) return false;
            if (decompSize - copyPlace > numBytes) return false;
            memmove(decomp + dstPlace, decomp + copyPlace, numBytes);
        }

        //Set up for the next read cycle
        codeByte &= 0x7F;
        codeByte <<= 1;
        bitCount--;
    }
    return true;
}

}
}
