#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdint>
#include <set>
using namespace std;

#define GAME_SIZE 67108864
#define DEBUG true
#define NUM_ITEMS 29
#define NUM_CHESTS 29
#define NUM_COMBOS 8

void ErrorCheck(int, char**);

struct Args
{
	struct Item* items[NUM_ITEMS];
	int num_progression;
	void makeItems();
	void sortItems();
	void makeCombo();

	struct Chest* chests[NUM_CHESTS];
	struct Chest* combos[NUM_COMBOS];	
	int chests_available;
	void makeChests();
	void sortChests();

	set<uint8_t> combo;
	void randomise();
	void checkCombo(uint8_t);
};

#include "chests.h"
#include "items.h"

int main(int argc, char** argv)
{
	Args arg;
	FILE* input;
	FILE* output;
	string name;
	uint8_t* data;
	uint8_t temp;
	uint32_t seed;
	int32_t i;

	ErrorCheck(argc, argv);

	//Get and set the seed
	srand(time(NULL));
	(argc == 3) ? seed = atoi(argv[2]) : seed = rand();
	srand(seed);
	
	printf("SEED: %d\n", seed);

	//Fill items and chests arrays
	arg.makeChests();
	arg.makeItems();

	//Count available chests and progression items
	for(i = 0; i < NUM_CHESTS; i++)
		if(arg.chests[i]->available)
			arg.chests_available++;
	printf("Chests available: %d\n", arg.chests_available);
	
	for(i = 0; i < NUM_ITEMS; i++)
		if(arg.items[i]->unlocks.size() != 0)
			arg.num_progression++;
	printf("Num Progression: %d\n", arg.num_progression);

	//Read the data from the source ROM
	data = new uint8_t[GAME_SIZE];
	input = fopen(argv[1], "rb");
	fread(data, GAME_SIZE, 1, input);
	fclose(input);

	//Sort the chests and items
	//Call the randomiser
	arg.sortChests();
	arg.sortItems();
	arg.randomise();

	//Optionally print out chest and item data
	if(DEBUG)
	{
		printf("Chests:\n");
		for(i = 0; i < NUM_CHESTS; i++)
			printf("Name: %s - Flags: 0x%04x - Used: %d - Available: %d\n", arg.chests[i]->name.c_str(), arg.chests[i]->flags, arg.chests[i]->used, arg.chests[i]->available);

		printf("Items:\n");
		for(i = 0; i < NUM_ITEMS; i++)
			printf("Name: %s - Used: %d\n", arg.items[i]->name.c_str(), arg.items[i]->used);
	}

	//Edit the data with new chest values
	for(i = 0; i < NUM_CHESTS; i++)
	{
		temp = arg.chests[i]->flags >> 8;
		*(data + (arg.chests[i]->offset)) = temp;
		temp = arg.chests[i]->flags;
		*(data + (arg.chests[i]->offset+1))  = temp;
	}

	//Write the edited data to a new file
	name = "ZOoTR_", name += to_string(seed), name += ".z64";
	output = fopen(name.c_str(), "wb");
	fwrite(data, GAME_SIZE, 1, output);
	fclose(output);
	delete[] data;

	//Optionally print out chest and item data
	if(0)
	{
		printf("Chests:\n");
		for(i = 0; i < NUM_CHESTS; i++)
			printf("Name: %s - Flags: %d - Used: %d\n", arg.chests[i]->name.c_str(), arg.chests[i]->flags ,arg.chests[i]->used);

		printf("Items:\n");
		for(i = 0; i < NUM_ITEMS; i++)
			printf("Name: %s - Used: %d\n", arg.items[i]->name.c_str(), arg.items[i]->used);
	}

	//Free up memory
	for(i = 0; i < NUM_CHESTS; i++)
		delete arg.chests[i];
	
	return(0);
}

void Args::randomise()
{
	int i = 0;
	int j, rChest, rItem;

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

		//Combine the item's chest value, and the chest's id value to place the
		//item in the chest, then set some flags for the next iteration to use
		chests[rChest]->flags = chests[rChest]->flags & 0xF01F;
		chests[rChest]->flags = chests[rChest]->flags | items[rItem]->chest_id;
		chests[rChest]->available = false;
		combo.insert(items[rItem]->id);
		chests[rChest]->used = true;
		items[rItem]->used = true;
		chests_available--;

		//If the item was a progression item, unlock the chests in it's unlocks vector
		if(items[rItem]->unlocks.size() != 0)
		{
			num_progression--;

			for(j = 0; j < items[rItem]->unlocks.size(); j++)
			{
				if(items[rItem]->unlocks[j]->used)
					continue;
				if(!items[rItem]->unlocks[j]->available)
				{
					items[rItem]->unlocks[j]->available = true;
					chests_available++;
				}
			}
		}

		printf("%s in %s\n", items[rItem]->name.c_str(), chests[rChest]->name.c_str());
		checkCombo(items[rItem]->id);

		//Sort the chests and items again
		sortChests();
		sortItems();
		i++;
	}
}

/*
	Function: checkCombo
	Purpose: Checks for item pairs that can be used to unlock chests
	Paramaters: Item A's id
	Returns: N/A
*/
void Args::checkCombo(uint8_t id)
{
	//Ocarina of Time
	if(id == 0x0C)
	{
		//Bombs
		if(combo.find(0x32) != combo.end())
		{
			//Zora's Domain Chest
			if(!combos[6]->used and !combos[6]->available)
			{
				combos[6]->available = true;
				chests_available++;
			}
		}

		//Din's Fire
		if(combo.find(0x5C) != combo.end())
		{
			//Royal Family Tomb Chest
			if(!combos[5]->used and !combos[5]->available)
			{
				combos[5]->available = true;
				chests_available++;
			}
		}

		return;
	}

	//Din's Fire
	if(id == 0x5C)
	{
		//Ocarina of Time
		if(combo.find(0x0C) != combo.end())
		{
			//Royal Family Tomb Chest
			if(!combos[5]->used and !combos[5]->available)
			{
				combos[5]->available = true;
				chests_available++;
			}
		}
	}

	//Bombs
	if(id == 0x32)
	{
		//Slingshot
		if(combo.find(0x05) != combo.end())
		{
			//DC small chest (bridge)
			if(!combos[0]->used and !combos[0]->available)
			{
				combos[0]->available = true;
				chests_available++;
			}

			//DC Bomb bag chest
			if(!combos[1]->used and !combos[1]->available)
			{
				combos[1]->available = true;
				chests_available++;
			}

			//DC small chest (boss room)
			if(!combos[7]->used and !combos[7]->available)
			{
				combos[7]->available = true;
				chests_available++;
			}
		}

		//Ocarina of Time
		if(combo.find(0x0C) != combo.end())
		{
			//Zora's Domain Chest
			if(!combos[6]->used and !combos[6]->available)
			{
				combos[6]->available = true;
				chests_available++;
			}
		}

		//Bottle
		if(combo.find(0x0F) != combo.end())
		{
			//Zora's Domain Chest
			if(!combos[6]->used and !combos[6]->available)
			{
				combos[6]->available = true;
				chests_available++;
			}
		}

		return;
	}

	//Goron Bracelet
	if(id == 0x54)
	{
		//Slingshot
		if(combo.find(0x05) != combo.end())
		{
			//DC Bomb bag chest
			if(!combos[1]->used and !combos[1]->available)
			{
				combos[1]->available = true;
				chests_available++;
			}
		}

		return;
	}

	//Slingshot
	if(id == 0x05)
	{
		//Goron Bracelet
		if(combo.find(0x54) != combo.end())
		{
			//DC Bomb bag chest
			if(!combos[1]->used and !combos[1]->available)
			{
				combos[1]->available = true;
				chests_available++;
			}
		}

		//Bombs
		if(combo.find(0x32) != combo.end())
		{
			//DC small chest (bridge)
			if(!combos[0]->used and !combos[0]->available)
			{
				combos[0]->available = true;
				chests_available++;
			}

			//DC Bomb bag chest
			if(!combos[1]->used and !combos[1]->available)
			{
				combos[1]->available = true;
				chests_available++;
			}

			//DC small chest (boss room)
			if(!combos[7]->used and !combos[7]->available)
			{
				combos[7]->available = true;
				chests_available++;
			}
		}

		//Bottle
		if(combo.find(0x0F) != combo.end())
		{
			//JJ Boomerang Chest 
			if(!combos[4]->used and !combos[4]->available)
			{
				combos[4]->available = true;
				chests_available++;
			}
		}

		return;
	}

	//Boomerang
	if(id == 0x06)
	{
		//Bottle
		if(combo.find(0x0F) != combo.end())
		{
			//JJ Compass Chest
			if(!combos[2]->used and !combos[2]->available)
			{
				combos[2]->available = true;
				chests_available++;
			}

			//JJ Map Chest
			if(!combos[3]->used and !combos[3]->available)
			{
				combos[3]->available = true;
				chests_available++;
			}

			//JJ Boomerang Chest
			if(!combos[4]->used and !combos[4]->available)
			{
				combos[4]->available = true;
				chests_available++;
			}
		}

		return;
	}

	//Bottle
	if(id == 0x0F)
	{
		//Boomerang
		if(combo.find(0x06) != combo.end())
		{
			//JJ Compass Chest
			if(!combos[2]->used and !combos[2]->available)
			{
				combos[2]->available = true;
				chests_available++;
			}

			//JJ Map Chest
			if(!combos[3]->used and !combos[3]->available)
			{
				combos[3]->available = true;
				chests_available++;
			}

			//JJ Boomerang Chest
			if(!combos[4]->used and !combos[4]->available)
			{
				combos[4]->available = true;
				chests_available++;
			}
		}

		//Bombs
		if(combo.find(0x32) != combo.end())
		{
			//JJ Boomerang Chest 
			if(!combos[4]->used and !combos[4]->available)
			{
				combos[4]->available = true;
				chests_available++;
			}
		}

		//Slingshot
		if(combo.find(0x05) != combo.end())
		{
			//JJ Boomerang Chest 
			if(!combos[4]->used and !combos[4]->available)
			{
				combos[4]->available = true;
				chests_available++;
			}
		}

		return;
	}	
}

/*
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
*/

/*
	Function: ErrorCheck
	Purpose: All of the error checking in one function to make it pretty
	Paramaters: Argc and Argv
	Returns: N/A
*/
void ErrorCheck(int argc, char** argv)
{
	FILE* input;

	if(argc < 2 or argc > 3)
	{
		fprintf(stderr, "Usage: Randomise file_name [Seed]\n");
		exit(1);
	}

	input = fopen(argv[1], "rb");
	if(input == NULL)
	{
		perror(argv[1]);
		fclose(input);
		exit(1);
	}
}
