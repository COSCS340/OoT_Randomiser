#ifndef CHESTS_H
#define CHESTS_H

#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;

#define NUM_CHESTS 28

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
	chests = new Chest*[NUM_CHESTS];
	chests_available = 0;
 
	//Mido's House (Top Left)
	chests[0] = new Chest;
	chests[0]->name = "Mido's House 0";
	chests[0]->offset = 0x02f7b08a;
	chests[0]->flags = 0x59A0;
	chests[0]->available = true;
	chests[0]->used = false;

	//Mido's House (Top Right)
	chests[1] = new Chest;
	chests[1]->name = "Mido's House 1";
	chests[1]->offset = 0x02f7b09a;
	chests[1]->flags = 0x59A1;
	chests[1]->available = true;
	chests[1]->used = false;

	//Mido's House (Bottom Left)
	chests[2] = new Chest;
	chests[2]->name = "Mido's House 2";
	chests[2]->offset = 0x02f7b0aa;
	chests[2]->flags = 0x5982;
	chests[2]->available = true;
	chests[2]->used = false;

	//Mido's House (Bottom Right)
	chests[3] = new Chest;
	chests[3]->name = "Mido's House 3";
	chests[3]->offset = 0x02f7b0ba;
	chests[3]->flags = 0x5903;
	chests[3]->available = true;
	chests[3]->used = false;

	//Kokiri Forest (Kokiri Sword Chest)
	chests[4] = new Chest;
	chests[4]->name = "Kokiri Sword Chest";
	chests[4]->offset = 0x020a6142;
	chests[4]->flags = 0x04E0;
	chests[4]->available = true;
	chests[4]->used = false;

	//Deku Tree Map Chest
	chests[5] = new Chest;
	chests[5]->name = "DT Map Chest";
	chests[5]->offset = 0x024a7138;
	chests[5]->flags = 0x0823;
	chests[5]->available = true;
	chests[5]->used = false;

	//Deku Tree Slingshot Chest
	chests[6] = new Chest;
	chests[6]->name = "DT Slingshot Chest";
	chests[6]->offset = 0x024c20b8;
	chests[6]->flags = 0x00a1;
	chests[6]->available = true;
	chests[6]->used = false;

	//Deku Tree Heart Chest (Slingshot room)
	chests[7] = new Chest;
	chests[7]->name = "DT S Heart Chest";
	chests[7]->offset = 0x024c20c8;
	chests[7]->flags = 0x5905;
	chests[7]->available = true;
	chests[7]->used = false;

	//Deku Tree Basement Chest
	chests[8] = new Chest;
	chests[8]->name = "DT Basement Chest";
	chests[8]->offset = 0x024c8158;
	chests[8]->flags = 0x5904;
	chests[8]->available = true;
	chests[8]->used = false;

	//Deku Tree Compass Chest
	chests[9] = new Chest;
	chests[9]->name = "DT Compass Chest";
	chests[9]->offset = 0x025040c8;
	chests[9]->flags = 0x0802;
	chests[9]->available = true;
	chests[9]->used = false;

	//Deku Tree Heart Chest (Compass room)
	chests[10] = new Chest;
	chests[10]->name = "DT C Heart Chest";
	chests[10]->offset = 0x025040d8;
	chests[10]->flags = 0x5906;
	chests[10]->available = true;
	chests[10]->used = false;

	//DC Map Chest
	chests[11] = new Chest;
	chests[11]->name = "DC Map Chest";
	chests[11]->offset = 0x01f2819e;
	chests[11]->flags = 0x0828;
	chests[11]->available = false;
	chests[11]->used = false;

	//DC Deku Shield Chest
	chests[12] = new Chest;
	chests[12]->name = "DC Deku Shield Chest";
	chests[12]->offset = 0x01f281ce;
	chests[12]->flags = 0x552a;
	chests[12]->available = false;
	chests[12]->used = false;

	//DC Bomb Bag Chest
	chests[13] = new Chest;
	chests[13]->name = "DC Bomb Bag Chest";
	chests[13]->offset = 0x01f890ce;
	chests[13]->flags = 0x0644;
	chests[13]->available = false;
	chests[13]->used = false;

	//DC Red Rupee Chest
	chests[14] = new Chest;
	chests[14]->name = "DC Red Rupee Chest";
	chests[14]->offset = 0x01f890de;
	chests[14]->flags = 0x59c6;
	chests[14]->available = false;
	chests[14]->used = false;

	//DC Compass Chest
	chests[15] = new Chest;
	chests[15]->name = "DC Compass Chest";
	chests[15]->offset = 0x01faf0aa;
	chests[15]->flags = 0x0805;
	chests[15]->available = false;
	chests[15]->used = false;

	//JJ Compass Chest
	chests[16] = new Chest;
	chests[16]->name = "JJ Compass Chest";
	chests[16]->offset = 0x02796000;
	chests[16]->flags = 0xb804;
	chests[16]->available = false;
	chests[16]->used = false;

	//JJ Map Chest
	chests[17] = new Chest;
	chests[17]->name = "JJ Map Chest";
	chests[17]->offset = 0x0278000;
	chests[17]->flags = 0x1822;
	chests[17]->available = false;
	chests[17]->used = false;

	//JJ Boomerang Chest
	chests[18] = new Chest;
	chests[18]->name = "JJ Bomerang Chest";
	chests[18]->offset = 0x0278a0000;
	chests[18]->flags = 0x10c1;
	chests[18]->available = false;
	chests[18]->used = false;

	//Fairy Fountian Grave
	chests[19] = new Chest;
	chests[19]->name = "Fairy Fountain Grave";
	chests[19]->offset = 0x0328b096;
	chests[19]->flags = 0x5540;
	chests[19]->available = true;
	chests[19]->used = false;

	//Redead Grave
	chests[20] = new Chest;
	chests[20]->name = "Redead Grave";
	chests[20]->offset = 0x02d0a056;
	chests[20]->flags = 0xa7c0;
	chests[20]->available = false;
	chests[20]->used = false;

	//Royal Family Tomb
	chests[21] = new Chest;
	chests[21]->name = "Royal Family Tomb";
	chests[21]->offset = 0x0332d0ea;
	chests[21]->flags = 0x8020;
	chests[21]->available = false;
	chests[21]->used = false;

	//GC Rock Room 200r Chest
	chests[22] = new Chest;
	chests[22]->name = "GC Rock Room 200R";
	chests[22]->offset = 0x0227c23a;
	chests[22]->flags = 0x5ac0;
	chests[22]->available = false;
	chests[22]->used = false;

	//GC Rock Room Right Chest
	chests[23] = new Chest;
	chests[23]->name = "GC Rock Room Right";
	chests[23]->offset = 0x0227c24a;
	chests[23]->flags = 0x5aa1;
	chests[23]->available = false;
	chests[23]->used = false;

	//GC Rock Room Left Chest
	chests[24] = new Chest;
	chests[24]->name = "GC Rock Room Left";
	chests[24]->offset = 0x0227c25a;
	chests[24]->flags = 0x5aa2;
	chests[24]->available = false;
	chests[24]->used = false;

	//GC Rock Room PoH Chest
	chests[25] = new Chest;
	chests[25]->name = "Zora's Domian PoH Chest";
	chests[25]->offset = 0x02103166;
	chests[25]->flags = 0xb7c0;
	chests[25]->available = false;
	chests[25]->used = false;

	//Redead Grotto Chest
	chests[26] = new Chest;
	chests[26]->name = "Redead Grotto";
	chests[26]->offset = 0x026cf076;
	chests[26]->flags = 0x7aca;
	chests[26]->available = false;
	chests[26]->used = false;

	//Death Mountian Trail
	chests[27] = new Chest;
	chests[27]->name = "Death Mountian Trail";
	chests[27]->offset = 0x0223c3ca;
	chests[27]->flags = 0x5aa1;
	chests[27]->available = false;
	chests[27]->used = false;
}

void Args::sortChests()
{
	for(int i = 0; i < NUM_CHESTS; i++)
		for(int j = 0; j < NUM_CHESTS-i-1; j++)
			if(*chests[j+1] < *chests[j])
				swap(chests[j+1], chests[j]);
}

#endif
