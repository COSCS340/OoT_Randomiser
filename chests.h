#ifndef CHESTS_H
#define CHESTS_H

#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;

#define NUM_CHESTS 5

void sortChests();
void makeChests();

struct Chest
{
	string name;				/*Name of chest location*/
	unsigned int offset;		/*Location of the chest in game data*/
	unsigned short flags;	/*Chest type and Chest flag*/
	bool available;			/*If the chest is available to place items in*/
	bool used;					/*If the chest has been used already*/
	bool operator<(const Chest& c) {return(this->available > c.available);}
};

Chest** chests;
int chests_available = 0;

void makeChests()
{
	chests = (Chest**)malloc(sizeof(Chest*) * NUM_CHESTS);

	//Mido's House (Top Left)
	chests[0] = new Chest;
	chests[0]->name = "Mido's House 0";
	chests[0]->offset = 0x02f7b08a;
	chests[0]->flags = 0x5000;
	chests[0]->available = false;
	chests[0]->used = false;

	//Mido's House (Top Right)
	chests[1] = new Chest;
	chests[1]->name = "Mido's House 1";
	chests[1]->offset = 0x02f7b09a;
	chests[1]->flags = 0x5001;
	chests[1]->available = false;
	chests[1]->used = false;

	//Mido's House (Bottom Left)
	chests[2] = new Chest;
	chests[2]->name = "Mido's House 2";
	chests[2]->offset = 0x02f7b0aa;
	chests[2]->flags = 0x5002;
	chests[2]->available = false;
	chests[2]->used = false;

	//Mido's House (Bottom Right)
	chests[3] = new Chest;
	chests[3]->name = "Mido's House 3";
	chests[3]->offset = 0x02f7b0ba;
	chests[3]->flags = 0x5003;
	chests[3]->available = false;
	chests[3]->used = false;

	//Kokiri Forest (Kokiri Sword Chest)
	chests[4] = new Chest;
	chests[4]->name = "Kokiri Sword Chest";
	chests[4]->offset = 0x020a6142;
	chests[4]->flags = 0x0000;
	chests[4]->available = true;
	chests[4]->used = false;
}

void sortChests()
{
	for(int i = 0; i < NUM_CHESTS; i++)
		for(int j = 0; j < NUM_CHESTS-i-1; j++)
			if(*chests[j+1] < *chests[j])
				swap(chests[j], chests[j+1]);
}

#endif
