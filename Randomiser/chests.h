#ifndef CHESTS_H
#define CHESTS_H

#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;

struct Chest
{
	string name;            /*Name of chest location*/
	unsigned int offset;    /*Location of the chest in game data*/
	unsigned short flags;   /*Chest type and Chest flag*/
	bool available;         /*If the chest is available to place items in*/
	bool used;              /*If the chest has been used already*/
	bool operator<(const Chest& c) {return(this->available > c.available);}
};

void Args::makeChests()
{
	Chest* chest;
	chests_available = 0;
 
	//Mido's House (Top Left)
	chest = new Chest;
	chest->name = "Mido's House 0";
	chest->offset = 0x02f7b08a;
	chest->flags = 0x59A0;
	chest->available = true;
	chest->used = false;
	chests[0] = chest;

	//Mido's House (Top Right)
	chest = new Chest;
	chest->name = "Mido's House 1";
	chest->offset = 0x02f7b09a;
	chest->flags = 0x59A1;
	chest->available = true;
	chest->used = false;
	chests[1] = chest;

	//Mido's House (Bottom Left)
	chest = new Chest;
	chest->name = "Mido's House 2";
	chest->offset = 0x02f7b0aa;
	chest->flags = 0x5982;
	chest->available = true;
	chest->used = false;
	chests[2] = chest;

	//Mido's House (Bottom Right)
	chest = new Chest;
	chest->name = "Mido's House 3";
	chest->offset = 0x02f7b0ba;
	chest->flags = 0x5903;
	chest->available = true;
	chest->used = false;
	chests[3] = chest;

	//Kokiri Forest (Kokiri Sword Chest)
	chest = new Chest;
	chest->name = "Kokiri Sword Chest";
	chest->offset = 0x020a6142;
	chest->flags = 0x04E0;
	chest->available = true;
	chest->used = false;
	chests[4] = chest;

	//Deku Tree Map Chest
	chest = new Chest;
	chest->name = "DT Map Chest";
	chest->offset = 0x024a7138;
	chest->flags = 0x0823;
	chest->available = true;
	chest->used = false;
	chests[5] = chest;

	//Deku Tree Slingshot Chest
	chest = new Chest;
	chest->name = "DT Slingshot Chest";
	chest->offset = 0x024c20b8;
	chest->flags = 0x00a1;
	chest->available = true;
	chest->used = false;
	chests[6] = chest;

	//Deku Tree Heart Chest (Slingshot room)
	chest = new Chest;
	chest->name = "DT S Heart Chest";
	chest->offset = 0x024c20c8;
	chest->flags = 0x5905;
	chest->available = true;
	chest->used = false;
	chests[7] = chest;

	//Deku Tree Basement Chest
	chest = new Chest;
	chest->name = "DT Basement Chest";
	chest->offset = 0x024c8158;
	chest->flags = 0x5904;
	chest->available = true;
	chest->used = false;
	chests[8] = chest;

	//Deku Tree Compass Chest
	chest = new Chest;
	chest->name = "DT Compass Chest";
	chest->offset = 0x025040c8;
	chest->flags = 0x0802;
	chest->available = true;
	chest->used = false;
	chests[9] = chest;

	//Deku Tree Heart Chest (Compass room)
	chest = new Chest;
	chest->name = "DT C Heart Chest";
	chest->offset = 0x025040d8;
	chest->flags = 0x5906;
	chest->available = true;
	chest->used = false;
	chests[10] = chest;

	//DC Map Chest
	chest = new Chest;
	chest->name = "DC Map Chest";
	chest->offset = 0x01f2819e;
	chest->flags = 0x0828;
	chest->available = false;
	chest->used = false;
	chests[11] = chest;

	//DC Deku Shield Chest
	chest = new Chest;
	chest->name = "DC Deku Shield Chest";
	chest->offset = 0x01f281ce;
	chest->flags = 0x552a;
	chest->available = false;
	chest->used = false;
	chests[12] = chest;
	combos[0] = chest;

	//DC Bomb Bag Chest
	chest = new Chest;
	chest->name = "DC Bomb Bag Chest";
	chest->offset = 0x01f890ce;
	chest->flags = 0x0644;
	chest->available = false;
	chest->used = false;
	chests[13] = chest;
	combos[1] = chest;

	//DC Spike Trap Room
	chest = new Chest;
	chest->name = "DC Red Rupee Chest";
	chest->offset = 0x01f890de;
	chest->flags = 0x59c6;
	chest->available = false;
	chest->used = false;
	chests[14] = chest;

	//DC Compass Chest
	chest = new Chest;
	chest->name = "DC Compass Chest";
	chest->offset = 0x01faf0aa;
	chest->flags = 0x0805;
	chest->available = false;
	chest->used = false;
	chests[15] = chest;

	//JJ Compass Chest
	chest = new Chest;
	chest->name = "JJ Compass Chest";
	chest->offset = 0x02796000;
	chest->flags = 0xb804;
	chest->available = false;
	chest->used = false;
	chests[16] = chest;
	combos[2] = chest;

	//JJ Map Chest
	chest = new Chest;
	chest->name = "JJ Map Chest";
	chest->offset = 0x0278000;
	chest->flags = 0x1822;
	chest->available = false;
	chest->used = false;
	chests[17] = chest;
	combos[3] = chest;

	//JJ Boomerang Chest
	chest = new Chest;
	chest->name = "JJ Bomerang Chest";
	chest->offset = 0x0278a000;
	chest->flags = 0x10c1;
	chest->available = false;
	chest->used = false;
	chests[18] = chest;
	combos[4] = chest;

	//Fairy Fountian Grave
	chest = new Chest;
	chest->name = "Fairy Fountain Grave";
	chest->offset = 0x0328b096;
	chest->flags = 0x5540;
	chest->available = true;
	chest->used = false;
	chests[19] = chest;

	//Redead Grave
	chest = new Chest;
	chest->name = "Redead Grave";
	chest->offset = 0x02d0a056;
	chest->flags = 0xa7c0;
	chest->available = false;
	chest->used = false;
	chests[20] = chest;

	//Royal Family Tomb
	chest = new Chest;
	chest->name = "Royal Family Tomb";
	chest->offset = 0x0332d0ea;
	chest->flags = 0x8020;
	chest->available = false;
	chest->used = false;
	chests[21] = chest;
	combos[5] = chest;

	//GC Rock Room 200r Chest
	chest = new Chest;
	chest->name = "GC Rock Room 200R";
	chest->offset = 0x0227c23a;
	chest->flags = 0x5ac0;
	chest->available = false;
	chest->used = false;
	chests[22] = chest;

	//GC Rock Room Right Chest
	chest = new Chest;
	chest->name = "GC Rock Room Right";
	chest->offset = 0x0227c24a;
	chest->flags = 0x5aa1;
	chest->available = false;
	chest->used = false;
	chests[23] = chest;

	//GC Rock Room Left Chest
	chest = new Chest;
	chest->name = "GC Rock Room Left";
	chest->offset = 0x0227c25a;
	chest->flags = 0x5aa2;
	chest->available = false;
	chest->used = false;
	chests[24] = chest;

	//Zora's Domain Room PoH Chest
	chest = new Chest;
	chest->name = "Zora's Domin PoH Chest";
	chest->offset = 0x02103166;
	chest->flags = 0xb7c0;
	chest->available = false;
	chest->used = false;
	chests[25] = chest;
	combos[6] = chest;

	//Redead Grotto Chest
	chest = new Chest;
	chest->name = "Redead Grotto";
	chest->offset = 0x026cf076;
	chest->flags = 0x7aca;
	chest->available = false;
	chest->used = false;
	chests[26] = chest;

	//Death Mountian Trail
	chest = new Chest;
	chest->name = "Death Mountian Trail";
	chest->offset = 0x0223c3ca;
	chest->flags = 0x5aa1;
	chest->available = false;
	chest->used = false;
	chests[27] = chest;

	//King Dodongo's Room
	chest = new Chest;
	chest->name = "King Dodongo's Room";
	chest->offset = 0x02eb00ba;
	chest->flags = 0x5020;
	chest->available = false;
	chest->used = false;
	chests[28] = chest;
	combos[7] = chest;
}

void Args::sortChests()
{
	for(int i = 0; i < NUM_CHESTS; i++)
		for(int j = 0; j < NUM_CHESTS-i-1; j++)
			if(*chests[j+1] < *chests[j])
				swap(chests[j+1], chests[j]);
}

#endif
