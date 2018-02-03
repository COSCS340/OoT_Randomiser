#ifndef ITEMS_H
#define ITEMS_H

#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

#define NUM_ITEMS 14

struct Item
{
	bool used;						/*If item has been placed*/
	string name;					/*Name of the item*/
	unsigned char id;				/*Item number*/
	unsigned short chest_id;	/*Value to override chest data*/
	vector<Chest*> unlocks;		/*Chests that this item gives access to*/
	bool operator<(const Item&);
	bool operator==(const Item&) const;
};

void Args::makeItems()
{
	items = new Item*[NUM_ITEMS];
	num_progression = 0;

	items[0] = new Item;
	items[0]->name = "Fairy Slingshot";
	items[0]->id = 0x05;
	items[0]->chest_id = 0x00a0;
	items[0]->used = false;
	items[0]->unlocks.resize(0);
	items[0]->unlocks = {};
	//Unlocks: Bomb bag chest

	items[1] = new Item;
	items[1]->name = "Boomerang";
	items[1]->id = 0x06;
	items[1]->chest_id = 0x00c0;
	items[1]->used = false;
	items[1]->unlocks.resize(0);
	items[1]->unlocks = {};

	items[2] = new Item;
	items[2]->name = "Lens of Truth";
	items[2]->id = 0x0a;
	items[2]->chest_id = 0x0140;
	items[2]->used = false;
	items[2]->unlocks.resize(0);
	items[2]->unlocks = {};

	items[3] = new Item;
	items[3]->name = "Ocarina of Time";
	items[3]->id = 0x0C;
	items[3]->chest_id = 0x0180;
	items[3]->used = false;
	items[3]->unlocks.resize(0);
	items[3]->unlocks = {};

	items[4] = new Item;
	items[4]->name = "Empty Bottle";
	items[4]->id = 0x0F;
	items[4]->chest_id = 0x01E0;
	items[4]->used = false;
	items[4]->unlocks.resize(0);
	items[4]->unlocks = {};

	items[5] = new Item;
	items[5]->name = "Empty Bottle";
	items[5]->id = 0x0F;
	items[5]->chest_id = 0x01E0;
	items[5]->used = false;
	items[5]->unlocks.resize(0);
	items[5]->unlocks = {};

	items[6] = new Item;
	items[6]->name = "Empty Bottle";
	items[6]->id = 0x0F;
	items[6]->chest_id = 0x01E0;
	items[6]->used = false;
	items[6]->unlocks.resize(0);
	items[6]->unlocks = {};

	items[7] = new Item;
	items[7]->name = "Empty Bottle";
	items[7]->id = 0x0F;
	items[7]->chest_id = 0x01E0;
	items[7]->used = false;
	items[7]->unlocks.resize(0);
	items[7]->unlocks = {};

	items[8] = new Item;
	items[8]->name = "Kokiri Sword";
	items[8]->id = 0x27;
	items[8]->chest_id = 0x04e0;
	items[8]->used = false;
	items[8]->unlocks.resize(0);
	items[8]->unlocks = {};

	items[9] = new Item;
	items[9]->name = "Deku Shield";
	items[9]->id = 0x29;
	items[9]->chest_id = 0x0520;
	items[9]->used = false;
	items[9]->unlocks.resize(0);
	items[9]->unlocks = {};

	items[10] = new Item;
	items[10]->name = "Hylian Shield";
	items[10]->id = 0x2A;
	items[10]->chest_id = 0x0540;
	items[10]->used = false;
	items[10]->unlocks.resize(0);
	items[10]->unlocks = {};

	items[11] = new Item;
	items[11]->name = "Bomb Bag";
	items[11]->id = 0x32;
	items[11]->chest_id = 0x0640;
	items[11]->used = false;
	items[11]->unlocks.resize(0);
	items[11]->unlocks = {};

	items[12] = new Item;
	items[12]->name = "Golden Scale";
	items[12]->id = 0x38;
	items[12]->chest_id = 0x0700;
	items[12]->used = false;
	items[12]->unlocks.resize(0);
	items[12]->unlocks = {};

	items[13] = new Item;
	items[13]->name = "Giant Wallet";
	items[13]->id = 0x46;
	items[13]->chest_id = 0x08C0;
	items[13]->used = false;
	items[13]->unlocks.resize(0);
	items[13]->unlocks = {};	
}

void Args::makeCombo()
{
	combo = new Item*[3];
	combo[0] = items[0];
	combo[1] = items[1];
	combo[2] = items[2];
}

void Args::sortItems()
{
	for(int i = 0; i < NUM_ITEMS; i++)
		for(int j = 0; j < NUM_ITEMS-i-1; j++)
			if(*items[j+1] < *items[j])
				swap(items[j+1], items[j]);
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

bool Item::operator==(const Item& i) const
{
	return(this->id == i.id);
}

#endif
