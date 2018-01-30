#include <iostream>
#include <fstream>
#include <ctime>
#include "chests.h"
#include "items.h"
using namespace std;

#define GAME_SIZE 67108864
#define DEBUG true

void randomise();
bool ErrorCheck(int, char**);

int main(int argc, char** argv)
{
	ifstream input;
	ofstream output;
	string name;
	unsigned char* data;
	unsigned char temp;
	int i, seed;

	if(ErrorCheck(argc, argv))
		return(-1);

	//Get and set the seed;
	srand(time(NULL));
	(argc == 3) ? seed = atoi(argv[2]) : seed = rand();
	srand(seed);
	
	//Fill items and chests arrays
	makeChests();
	makeItems();

	//Count available chests and progression items
	for(i = 0; i < NUM_CHESTS; i++)
		if(chests[i]->available)
			chests_available++;

	for(i = 0; i < NUM_ITEMS; i++)
		if(items[i].unlocks.size() != 0)
			num_progression++;

	//Read the data from the source ROM
	data = (unsigned char*)malloc(GAME_SIZE);
	input.open(argv[1], ios::binary);
	input.read(reinterpret_cast<char*>(data), GAME_SIZE);
	input.close();

	//Sort the chests availability
	//Sort the items by availibility, with progression items at the begining of the list
	//Call the randomiser
	sortChests();
	sort(items, items+NUM_ITEMS);
	randomise();

	//Edit the data with new chest values
	for(i = 0; i < NUM_CHESTS; i++)
	{
		temp = chests[i]->flags >> 8;
		data[chests[i]->offset] = temp;
		temp = chests[i]->flags;
		data[chests[i]->offset+1] = temp;
	}

	//Write the edited data to a new file
	name = "ZOoTR_", name += to_string(seed), name += ".z64";
	output.open(name, ios::binary);
	output.write(reinterpret_cast<const char*>(data), GAME_SIZE);
	output.close();
	free(data);

	//Optionally print out chest and item data
	if(DEBUG)
	{
		printf("Chests:\n");
		for(i = 0; i < NUM_CHESTS; i++)
			printf("Offset: 0x%08x - Flags: 0x%04x - Used: %i\n", chests[i]->offset, chests[i]->flags, chests[i]->used);

		printf("Items:\n");
		for(i = 0; i < NUM_ITEMS; i++)
			printf("Id: %02x, Chest_id: %04x\n", items[i].id, items[i].chest_id);
	}

	//Free up memory
	for(i = 0; i < NUM_CHESTS; i++)
		delete chests[i];
	delete[] chests;
	delete[] items;
	
	return(0);
}

void randomise()
{
	int i, rChest, rItem;

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
		chests[rChest]->flags = chests[rChest]->flags | items[rItem].chest_id;
		chests[rChest]->available = false;
		chests[rChest]->used = true;
		items[rItem].used = true;
		chests_available--;

		//If the item was a progression item, unlock the chests in it's unlocks vector
		if(items[rItem].unlocks.size() != 0)
		{
			num_progression--;

			for(i = 0; i < items[rItem].unlocks.size(); i++)
			{
				if(items[rItem].unlocks[i]->used)
					continue;
				if(!items[rItem].unlocks[i]->available)
				{
					items[rItem].unlocks[i]->available = true;
					chests_available++;
				}
			}
		}

		//Sort the chests and items again
		sortChests();
		sort(items, items+NUM_CHESTS);
	}
}

bool ErrorCheck(int argc, char** argv)
{
	ifstream input;

	if(argc < 2 or argc > 3)
	{
		printf("Usage: Randomise [File name] [Seed (Optional)]\n");
		return(true);
	}

	input.open(argv[1], ios::binary);
	if(input.fail())
	{
		printf("Error: File not found\n");
		input.close();
		return(true);
	}

	return(false);
}
