#include <iostream>
#include <endian.h>
#include <fstream>
#include <cstring>
#include <string>
#include <cmath>
#include <cstdint>
#include <cstddef>
#include <vector>

static bool ErrorCheck(int, char**);

static uint32_t from_arg(const char *arg) {
    if ((arg[0] >= '0' && arg[0] <= '9') || (arg[0] >= 'a' && arg[0] <= 'f') || (arg[0] >= 'A' && arg[0] <= 'F')) {
        char *endptr;
        errno = 0;
        unsigned long q = strtoul(arg, &endptr, 16);
        if (errno || *endptr || q > UINT32_MAX) {
            throw std::runtime_error("Invalid hex passed as argument");
        }
        return std::uint32_t(q);
    }
    throw std::runtime_error("Invalid hex passed as argument");
}

static void real_main(int argc, char **argv);
int main(int argc, char** argv)
{
    try {
        real_main(argc, argv);
        return 0;
    } catch (std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}


void real_main(int argc, char **argv) {
    std::uint32_t mapstart = 0, i = 0;
	unsigned char temp = 0;
    std::vector<unsigned char> data;
    std::ifstream input;
    std::ofstream output;
    std::ofstream textfile;

    std::cout.exceptions(std::iostream::badbit | std::iostream::failbit | std::iostream::eofbit);

    if(ErrorCheck(argc, argv))
        return;
    uint32_t start = from_arg(argv[2]);
    uint32_t end = from_arg(argv[3]);

	//Write scene offsets to txt file
    std::string name{argv[1]};
    name += ".txt";
    textfile.exceptions(std::iostream::badbit | std::iostream::failbit | std::iostream::eofbit);
    textfile.open(name);

    textfile << argv[1] << ":    " << "0" << std::hex << start << " - " << end << std::endl;

	//Get size, finish filename, make room for data
    std::uint32_t size = end-start;
    std::vector<char> buffer(size);
    name = argv[1];
    name += ".zscene";
	i = 0;
    input.exceptions(std::iostream::badbit | std::iostream::failbit | std::iostream::eofbit);

	//Read then write data to new file
    input.open("ZOOTDEC.z64", std::ios::binary);
    input.seekg(start, std::ios::beg);
    input.read(reinterpret_cast<char*>(data.data()), size);
    {
        std::ofstream output(name, std::ios::binary);
        output.exceptions(std::iostream::badbit | std::iostream::failbit | std::iostream::eofbit);
        output.write(reinterpret_cast<const char*>(data.data()), size);
        std::cout << name << " written" << std::endl;
    }

	//Get the map starting point offset
	//If a map is inside, start halfway through line 1, if outside, start on line 2
	if(tolower(argv[4][0]) == 'o')
        input.seekg(start+16, std::ios::beg);
	else
        input.seekg(start+8, std::ios::beg);

	//The starting point for map offsets is located 4 bytes after a 04xx with xx being the number of maps for the scene
	while(temp != 0x04)
		input.read(reinterpret_cast<char*>(&temp), 1);
	input.read(reinterpret_cast<char*>(&temp), 1);
    input.seekg(4, std::ios::cur);
	input.read(reinterpret_cast<char*>(&mapstart), 2);
    mapstart = be16toh(mapstart);
	mapstart += start;

	//Get map offsets, make files for each
    while(i < temp)
	{
        input.seekg(mapstart + (i*8), std::ios::beg);
        std::uint32_t start = 0, end = 0;

		input.read(reinterpret_cast<char*>(&start), 4);
		input.read(reinterpret_cast<char*>(&end), 4);
        if (input.bad() || input.eof() || input.fail()) {

        }
        start = be32toh(start);
        end = be32toh(end);

		//Write current map offsets to txt file
		if(i < 10)
            textfile << argv[1] << "-" << std::dec << i << ":  " << "0" << std::hex << start << " - "  << end << '\n';
		else
            textfile << argv[1] << "-" << std::dec << i << ": " << "0" << std::hex << start << " - "  << end << '\n';

		//Read and write the current map
		size = end-start;
        input.seekg(start, std::ios::beg);
        input.read(reinterpret_cast<char*>(data.data()), size);
        name = argv[1];
        name += '-';
        name += std::to_string(i);
        name += ".zmap";
        output.open(name, std::ios::binary);
        output.write(reinterpret_cast<const char*>(data.data()), size);
        std::cout << name << " written" << '\n';
		output.close();
		i++;
	}

	input.close();
	textfile.close();
}

bool ErrorCheck(int argc, char** argv)
{
    std::ifstream input;

	if(argc != 5)
	{
		printf("Usage: (Name of map) (Start offset) (End offset) (Indoor/Outdoor)\n");
		return true;
	}

	if(tolower(argv[4][0]) != 'i' and tolower(argv[4][0]) != 'o')
	{
		printf("Error: Need to specify indoor or outdoor map\n");
		return true;
	}

	if(strlen(argv[2]) != 8)
	{
		printf("Error: Starting offset needs to be 4 bytes (8 characters)\n");
        return true;
	}

	if(strlen(argv[3]) != 8)
	{
		printf("Error: Ending offset needs to be 4 bytes (8 characters)\n");
        return true;
	}

    input.open("ZOOTDEC.z64", std::ios::binary);
	if(input.fail())
	{
		printf("Error: ZOOTDEC.z64 not found\n");
		input.close();
        return true;
	}
	input.close();

    return false;
}
