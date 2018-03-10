#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdint>
#include <vector>
#include <memory>

#define GAME_SIZE 67108864
#define DEBUG true

bool ErrorCheck(int, char**);

#include "chests.h"
#include "items.h"


int main(int argc, char** argv)
{
    OoT_Randomizer::Args arg;
	FILE* input;
	FILE* output;
    std::string name;
	uint8_t temp;
	uint32_t seed;
	int32_t i;

	if(ErrorCheck(argc, argv))
		return(-1);

	//Get and set the seed
    std::srand(std::time(NULL));
	(argc == 3) ? seed = atoi(argv[2]) : seed = rand();
	srand(seed);

	//Count available chests and progression items
	for(i = 0; i < NUM_CHESTS; i++)
        if(arg.chests[i].available)
			arg.chests_available++;
	
	for(i = 0; i < NUM_ITEMS; i++)
        if(arg.items[i].unlocks.size() != 0)
			arg.num_progression++;

	//Read the data from the source ROM
    auto data = std::vector<uint8_t>(GAME_SIZE);
	input = fopen(argv[1], "rb");
    fread(data.data(), GAME_SIZE, 1, input);
	fclose(input);

	//Sort the chests and items
	//Call the randomiser
	arg.randomise();

	//Edit the data with new chest values
    for(const auto &chest: arg.chests)
	{
        data[chest.offset] = chest.flags >> 8;
        data[chest.offset+1] = chest.flags;
	}

	//Write the edited data to a new file
    static_cast<void>(name = "ZOoTR_"), static_cast<void>(name += std::to_string(seed)), name += ".z64";
	output = fopen(name.c_str(), "wb");
    fwrite(data.data(), GAME_SIZE, 1, output);
	fclose(output);

	//Optionally print out chest and item data
	if(DEBUG)
	{
		printf("Chests:\n");
        for(const auto &chest: arg.chests)
            printf("Offset: 0x%08x - Flags: 0x%04x - Used: %i\n", chest.offset, chest.flags, chest.used);

		printf("Items:\n");
        for(const auto &item: arg.items)
            printf("Id: %02x, Chest_id: %04x\n", item.id, item.chest_id);
	}
	
	return(0);
}

void OoT_Randomizer::Args::randomise()
{
	int i = 0;
	int rChest, rItem;

	while(chests_available > 0)
	{
		//Pick a random chest to put stuff in
		rChest = rand() % chests_available;

		//If it's the last available chest, and there are still progression items
		//then force a progression item to be placed, else pick a random item
		if(chests_available == 1 and num_progression != 0)
			rItem = rand() % num_progression;
		else
			rItem = rand() % (NUM_ITEMS-i);
        auto &chestRef = chests.at(rChest);
        auto &itemRef = items.at(rItem);
		//Combine the item's chest value, and the chest's id value to place the
		//item in the chest, then set some flags for the next iteration to use
        chestRef.flags &= 0xF01F;
        chestRef.flags |= itemRef.chest_id;
        chestRef.available = false;
        chestRef.used = true;
        itemRef.used = true;
		chests_available--;

		//If the item was a progression item, unlock the chests in it's unlocks vector
        if(itemRef.unlocks.size() != 0)
		{
			num_progression--;

            for(const auto & unlock: itemRef.unlocks)
			{
                if(unlock->used)
					continue;
                if(!unlock->available)
				{
                    unlock->available = true;
					chests_available++;
				}
			}
		}

        printf("%s in %s\n", itemRef.name.c_str(), chestRef.name.c_str());
		//Sort the chests and items again
		sortItems();
		i++;
	}
}
#if 0
void actorSetup(uint8_t* data)
{
	//Move Mido (X, Y, Z)
	data[x] = 0x0000;
	data[x] = 0x0010;
	data[x] = 0x0000;

	//Move other kokiri kid
	data[x] = 0x0000;
	data[x] = 0x0010;
	data[x] = 0x0000;

	//Open Death Mountian gate
	data[x] = 0xff9c;
	data[x] = 0x019a;
	data[x] = 0xfa9c;

	//Swap Silver Gauntlets with Green Rupee
	//Unimplemented, waiting to figure out progressive upgrades
}
#endif
bool ErrorCheck(int argc, char** argv)
{
	FILE* input;

	if(argc < 2 or argc > 3)
	{
		fprintf(stderr, "Usage: Randomise [File name] [Seed (Optional)]\n");
		return(true);
	}

	input = fopen(argv[1], "rb");
	if(input == NULL)
	{
		perror(argv[1]);
		fclose(input);
		return(true);
	}

	return(false);
}
