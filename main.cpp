#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

#define GAME_SIZE 67108864
#define DEBUG true

bool ErrorCheck(int, char**);

struct Args
{
	struct Item** items;
	struct Item** combo;
	int num_progression;
	void makeItems();
	void sortItems();
	void makeCombo();

	struct Chest** chests;
	int chests_available;
	void makeChests();
	void sortChests();

	void randomise();
};

#include "chests.h"
#include "items.h"

int main(int argc, char** argv)
{
	Args arg;
	ifstream input;
	ofstream output;
	string name;
	unsigned char* data;
	unsigned char temp;
	unsigned int seed;
	int i;

	if(ErrorCheck(argc, argv))
		return(-1);

	//Get and set the seed;
	srand(time(NULL));
	(argc == 3) ? seed = atoi(argv[2]) : seed = rand();
	srand(seed);
	
	//Fill items and chests arrays
	arg.makeChests();
	arg.makeItems();

	//Count available chests and progression items
	for(i = 0; i < NUM_CHESTS; i++)
		if(arg.chests[i]->available)
			arg.chests_available++;
	
	for(i = 0; i < NUM_ITEMS; i++)
		if(arg.items[i]->unlocks.size() != 0)
			arg.num_progression++;

	//Read the data from the source ROM
	data = (unsigned char*)malloc(GAME_SIZE);
	input.open(argv[1], ios::binary);
	input.read(reinterpret_cast<char*>(data), GAME_SIZE);
	input.close();

	//Sort the chests availability
	//Sort the items by availibility, with progression items at the begining of the list
	//Call the randomiser
	arg.sortChests();
	arg.sortItems();
	arg.randomise();

	//Edit the data with new chest values
	for(i = 0; i < NUM_CHESTS; i++)
	{
		temp = arg.chests[i]->flags >> 8;
		data[arg.chests[i]->offset] = temp;
		temp = arg.chests[i]->flags;
		data[arg.chests[i]->offset+1] = temp;
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
			printf("Offset: 0x%08x - Flags: 0x%04x - Used: %i\n", arg.chests[i]->offset, arg.chests[i]->flags, arg.chests[i]->used);

		printf("Items:\n");
		for(i = 0; i < NUM_ITEMS; i++)
			printf("Id: %02x, Chest_id: %04x\n", arg.items[i]->id, arg.items[i]->chest_id);
	}

	//Free up memory
	for(i = 0; i < NUM_CHESTS; i++)
		delete arg.chests[i];
	delete[] arg.chests;
	delete[] arg.items;
	
	return(0);
}

void Args::randomise()
{
	int i = 0, rChest, rItem;

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
		chests[rChest]->used = true;
		items[rItem]->used = true;
		chests_available--;

		//If the item was a progression item, unlock the chests in it's unlocks vector
		if(items[rItem]->unlocks.size() != 0)
		{
			num_progression--;

			for(i = 0; i < items[rItem]->unlocks.size(); i++)
			{
				if(items[rItem]->unlocks[i]->used)
					continue;
				if(!items[rItem]->unlocks[i]->available)
				{
					items[rItem]->unlocks[i]->available = true;
					chests_available++;
				}
			}
		}

		//Sort the chests and items again
		sortChests();
		sortItems();
		i++;
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
