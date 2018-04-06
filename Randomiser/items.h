#ifndef ITEMS_H
#define ITEMS_H

#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

struct Item
{
	string name;                 /*Name of the item*/
	uint8_t id;                  /*Item number*/
	uint16_t chest_id;           /*Value to override chest data*/
	bool used;                   /*If item has been placed*/
	vector<Chest*> unlocks;      /*Chests that this item gives access to*/
	bool operator<(const Item&);
	bool operator==(const Item&) const;
};

void Args::makeItems()
{
	Item* item;
	num_progression = 0;

	//Fairy Slingshot
	item = new Item;
	item->name = "Fairy Slingshot";
	item->id = 0x05;
	item->chest_id = 0x00a0;
	item->used = false;
	item->unlocks = {chests[0]};
	items[0] = item;

	//Boomerang
	item = new Item;
	item->name = "Boomerang";
	item->id = 0x06;
	item->chest_id = 0x00c0;
	item->used = false;
	item->unlocks = {chests[0]};
	items[1] = item;

	//Lens of Truth
	item = new Item;
	item->name = "Lens of Truth";
	item->id = 0x0a;
	item->chest_id = 0x0140;
	item->used = false;
	item->unlocks = {};
	items[2] = item;

	//Ocarina of Time
	item = new Item;
	item->name = "Ocarina of Time";
	item->id = 0x0C;
	item->chest_id = 0x0180;
	item->used = false;
	item->unlocks = {chests[0]};
	items[3] = item;

	//Bottle 1
	item = new Item;
	item->name = "Empty Bottle 1";
	item->id = 0x0F;
	item->chest_id = 0x01E0;
	item->used = false;
	item->unlocks = {chests[0]};
	items[4] = item;

	//Bottle 2
	item = new Item;
	item->name = "Empty Bottle 2";
	item->id = 0x0F;
	item->chest_id = 0x01E0;
	item->used = false;
	item->unlocks = {};
	items[5] = item;

	//Bottle 3
	item = new Item;
	item->name = "Empty Bottle 3";
	item->id = 0x0F;
	item->chest_id = 0x01E0;
	item->used = false;
	item->unlocks = {};
	items[6] = item;

	//Bottle 4
	item = new Item;
	item->name = "Empty Bottle 4";
	item->id = 0x0F;
	item->chest_id = 0x01E0;
	item->used = false;
	item->unlocks = {};
	items[7] = item;

	//Kokiri Sword
	item = new Item;
	item->name = "Kokiri Sword";
	item->id = 0x27;
	item->chest_id = 0x04e0;
	item->used = false;
	item->unlocks = {};
	items[8] = item;

	//Deku Shield
	item = new Item;
	item->name = "Deku Shield";
	item->id = 0x29;
	item->chest_id = 0x0520;
	item->used = false;
	item->unlocks = {};
	items[9] = item;

	//Hylian Shield
	item = new Item;
	item->name = "Hylian Shield";
	item->id = 0x2A;
	item->chest_id = 0x0540;
	item->used = false;
	item->unlocks = {};
	items[10] = item;

	//Bomb Bag (Default)
	item = new Item;
	item->name = "Bomb Bag";
	item->id = 0x32;
	item->chest_id = 0x0640;
	item->used = false;
	item->unlocks = {chests[11], chests[15], chests[14], chests[20], chests[22], chests[23], chests[24], chests[25], chests[26], chests[27]};
	items[11] = item;

	//Golden Scale
	item = new Item;
	item->name = "Golden Scale";
	item->id = 0x38;
	item->chest_id = 0x0700;
	item->used = false;
	item->unlocks = {chests[25]};
	items[12] = item;

	//Giant's Wallet
	item = new Item;
	item->name = "Giant Wallet";
	item->id = 0x46;
	item->chest_id = 0x08C0;
	item->used = false;
	item->unlocks = {};
	items[13] = item;

	//Din's Fire
	item = new Item;
	item->name = "Din's Fire";
	item->id = 0x5C;
	item->chest_id = 0x0B80;
	item->used = false;
	item->unlocks = {chests[0]};
	items[14] = item;

	//Farore's Wind
	item = new Item;
	item->name = "Farore's Wind";
	item->id = 0x5D;
	item->chest_id = 0x0BA0;
	item->used = false;
	item->unlocks = {};
	items[15] = item;

	//Nayru's Love
	item = new Item;
	item->name = "Nayru's Love";
	item->id = 0x5E;
	item->chest_id = 0x0BC0;
	item->used = false;
	item->unlocks = {};
	items[16] = item;

	//Goron Bracelet
	item = new Item;
	item->name = "Goron Bracelet";
	item->id = 0x54;
	item->chest_id = 0x0A80;
	item->used = false;
	item->unlocks = {chests[11], chests[14], chests[15]};
	items[17] = item;

	//Bombchus (10)
	item = new Item;
	item->name = "Bombchus (10) 1";
	item->id = 0x03;
	item->chest_id = 0x0060;
	item->used = false;
	item->unlocks = {};
	items[18] = item;

	//Bombchus (10)
	item = new Item;
	item->name = "Bombchus (10) 2";
	item->id = 0x03;
	item->chest_id = 0x0060;
	item->used = false;
	item->unlocks = {};
	items[19] = item;

	//Bombchus (10)
	item = new Item;
	item->name = "Bombchus (10) 3";
	item->id = 0x03;
	item->chest_id = 0x0060;
	item->used = false;
	item->unlocks = {};
	items[20] = item;

	//Rupees (50)
	item = new Item;
	item->name = "Purple Rupee 1";
	item->id = 0x55;
	item->chest_id = 0x0AA0;
	item->used = false;
	item->unlocks = {};
	items[21] = item;

	//Rupees (50)
	item = new Item;
	item->name = "Purple Rupee 2";
	item->id = 0x55;
	item->chest_id = 0x0AA0;
	item->used = false;
	item->unlocks = {};
	items[22] = item;

	//Rupees (50)
	item = new Item;
	item->name = "Purple Rupee 3";
	item->id = 0x55;
	item->chest_id = 0x0AA0;
	item->used = false;
	item->unlocks = {};
	items[23] = item;

	//Rupees (200)
	item = new Item;
	item->name = "Yellow Rupee 1";
	item->id = 0x56;
	item->chest_id = 0x0AC0;
	item->used = false;
	item->unlocks = {};
	items[24] = item;

	//Rupees (200)
	item = new Item;
	item->name = "Yellow Rupee 2";
	item->id = 0x56;
	item->chest_id = 0x0AC0;
	item->used = false;
	item->unlocks = {};
	items[25] = item;

	//Rupees (200)
	item = new Item;
	item->name = "Yellow Rupee 3";
	item->id = 0x56;
	item->chest_id = 0x0AC0;
	item->used = false;
	item->unlocks = {};
	items[26] = item;

	//Bombs (30)
	item = new Item;
	item->name = "Bombs (30) 1";
	item->id = 0x68;
	item->chest_id = 0x0D00;
	item->used = false;
	item->unlocks = {};
	items[27] = item;

	//Bombs (30)
	item = new Item;
	item->name = "Bombs (30) 2";
	item->id = 0x68;
	item->chest_id = 0x0D00;
	item->used = false;
	item->unlocks = {};
	items[28] = item;
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
