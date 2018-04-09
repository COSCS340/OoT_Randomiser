#ifndef CHESTS_H
#define CHESTS_H

#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
namespace OoT_Randomizer {

namespace Randomizer {

struct Chest
{
    std::string name;            /*Name of chest location*/
	unsigned int offset;    /*Location of the chest in game data*/
	unsigned short flags;   /*Chest type and Chest flag*/
	bool available;         /*If the chest is available to place items in*/
	bool used;              /*If the chest has been used already*/
	bool operator<(const Chest& c) {return(this->available > c.available);}
};

}

}

#endif
