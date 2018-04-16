/* snesrc - SNES Recompiler
 *
 * Copyright notice for this file:
 *  Copyright (C) 2005 Parasyte
 *
 * Based on uCON64's N64 checksum algorithm by Andreas Sterbenz
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

// April 15, 2018 - make OK for use in C++
#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

static inline uint32_t ROL(uint32_t i, uint8_t b) {
    assert(b && b < 32);
    b &= 31;
    return (i << b) | (i >> ((32 - b) & 31));
}

static inline uint32_t BYTES2LONG(unsigned char b[static 4]) {
    return ((uint32_t)( (b)[0] << 24 | \
                        (b)[1] << 16 | \
                        (b)[2] <<  8 | \
                        (b)[3] ));
}

#define N64_HEADER_SIZE  0x40
#define N64_BC_SIZE      (0x1000 - N64_HEADER_SIZE)

#define N64_CRC1         0x10
#define N64_CRC2         0x14

#define CHECKSUM_START   0x00001000
#define CHECKSUM_LENGTH  0x00100000
#define CHECKSUM_CIC6102 0xF8CA4DDC
#define CHECKSUM_CIC6103 0xA3886759
#define CHECKSUM_CIC6105 0xDF26F436
#define CHECKSUM_CIC6106 0x1FEA617A


static uint32_t crc_table[256];

// April 15, 2018 -- renamed with `OoT_Randomizer` prefix
void OoT_Randomizer_crc_init(void)
{
    uint32_t crc, poly, i, j;

	poly = 0xEDB88320;
	for (i = 0; i < 256; i++) {
		crc = i;
		for (j = 8; j > 0; j--) {
			if (crc & 1) crc = (crc >> 1) ^ poly;
			else crc >>= 1;
		}
		crc_table[i] = crc;
	}
}

static uint32_t crc32(unsigned char *data, size_t len)
{
    uint32_t crc = ~0U;
    size_t i;

	for (i = 0; i < len; i++) {
		crc = (crc >> 8) ^ crc_table[(crc ^ data[i]) & 0xFF];
	}

	return ~crc;
}


static uint32_t N64GetCIC(unsigned char *data)
{
	switch (crc32(&data[N64_HEADER_SIZE], N64_BC_SIZE)) {
		case 0x6170A4A1: return 6101;
		case 0x90BB6CB5: return 6102;
		case 0x0B050EE0: return 6103;
		case 0x98BC2C86: return 6105;
		case 0xACC8580A: return 6106;
	}

	return 0;
}

static bool N64CalcCRC(uint32_t *crc, unsigned char *data)
{
    uint32_t bootcode, i;
    uint32_t seed;

    uint32_t t1, t2, t3;
    uint32_t t4, t5, t6;
    uint32_t r, d;


	switch ((bootcode = N64GetCIC(data))) {
		case 6101:
		case 6102:
			seed = CHECKSUM_CIC6102;
			break;
		case 6103:
			seed = CHECKSUM_CIC6103;
			break;
		case 6105:
			seed = CHECKSUM_CIC6105;
			break;
		case 6106:
			seed = CHECKSUM_CIC6106;
			break;
		default:
			return 1;
	}

	t1 = t2 = t3 = t4 = t5 = t6 = seed;

	i = CHECKSUM_START;
	while (i < (CHECKSUM_START + CHECKSUM_LENGTH)) {
        d = (uint32_t)BYTES2LONG(&data[i]);
		if ((t6 + d) < t6) t4++;
		t6 += d;
		t3 ^= d;
		r = ROL(d, (d & 0x1F));
		t5 += r;
		if (t2 > d) t2 ^= r;
		else t2 ^= t6 ^ d;

		if (bootcode == 6105) t1 += BYTES2LONG(&data[N64_HEADER_SIZE + 0x0710 + (i & 0xFF)]) ^ d;
		else t1 += t5 ^ d;

		i += 4;
	}
	if (bootcode == 6103) {
		crc[0] = (t6 ^ t4) + t3;
		crc[1] = (t5 ^ t2) + t1;
	}
	else if (bootcode == 6106) {
		crc[0] = (t6 * t4) + t3;
		crc[1] = (t5 * t2) + t1;
	}
	else {
		crc[0] = t6 ^ t4 ^ t3;
		crc[1] = t5 ^ t2 ^ t1;
	}

	return 0;
}

void OoT_Randomizer_fix_crc (unsigned char *buffer, size_t size)
{
    unsigned char CRC1[4] = {0};
    unsigned char CRC2[4] = {0};
    uint32_t crc[2] = {0};
    if (size < CHECKSUM_START + CHECKSUM_LENGTH) abort();

    if (!N64CalcCRC(crc, buffer)) {
        size_t i;
        uint32_t kk1=crc[0];
        uint32_t kk2=crc[1];
		for(i=0;i<4;i++)
		{
		CRC1[i] = (kk1 >> (24-8*i))&0xFF;
		CRC2[i] = (kk2 >> (24-8*i))&0xFF;
		}
		
        if (crc[0] != (uint32_t)BYTES2LONG(&buffer[N64_CRC1])) {
            // April 15, 2018 -- place in brackets
            if (N64_CRC1 > size - sizeof (CRC1))
                abort();
            else
                memcpy(buffer + N64_CRC1, CRC1, sizeof (CRC1));
        }

        if (crc[1] != (uint32_t)BYTES2LONG(&buffer[N64_CRC2])) {
            // April 15, 2018 -- place in brackets
            if (N64_CRC2 > size - sizeof (CRC2))
                abort();
            else
                memcpy(buffer + N64_CRC2, CRC2, sizeof (CRC2));
		}
	}
}

// April 15, 2018 - make OK for use in C++
#ifdef __cplusplus
}
#endif
