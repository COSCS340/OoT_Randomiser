#ifndef ITEMS_H
#define ITEMS_H

#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

#define NUM_ITEMS 5

void makeItems();

struct Item
{
	bool used;						/*If item has been placed*/
	string name;					/*Name of the item*/
	unsigned char id;				/*Item number*/
	unsigned short chest_id;	/*Value to override chest data*/
	vector<Chest*> unlocks;		/*Chests that this item gives access to*/
	bool operator<(const Item& i);
};

Item* items;
int num_progression = 0;

void makeItems()
{
	items = (Item*)malloc(sizeof(Item) * NUM_ITEMS);
	
	items[0].name = "Bombchus (10)";
	items[0].id = 0x03;
	items[0].chest_id = 0x0060;
	items[0].used = false;
	items[0].unlocks.resize(4);
	items[0].unlocks = {chests[0], chests[1], chests[2], chests[3]};

	items[1].name = "Fairy Slingshot";
	items[1].id = 0x05;
	items[1].chest_id = 0x00a0;
	items[1].used = false;
	items[1].unlocks.resize(0);
	items[1].unlocks = {};

	items[2].name = "Boomerang";
	items[2].id = 0x06;
	items[2].chest_id = 0x00C0;
	items[2].used = false;
	items[2].unlocks.resize(0);
	items[2].unlocks = {};

	items[3].name = "Ocarina of Time";
	items[3].id = 0x0C;
	items[3].chest_id = 0x0180;
	items[3].used = false;
	items[3].unlocks.resize(0);
	items[3].unlocks = {};

	items[4].name = "Empty Bottle";
	items[4].id = 0x0F;
	items[4].chest_id = 0x01E0;
	items[4].used = false;
	items[4].unlocks.resize(0);
	items[4].unlocks = {};
}

bool Item::operator<(const Item& i)
{
	if(this->used < i.used)
		return(true);
	else if(this->used > i.used)
		return(false);
	else
		return(this->unlocks.size() > i.unlocks.size());
}

#endif
