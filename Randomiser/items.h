#ifndef OOT_RANDOMIZER_ITEMS_H
#define OOT_RANDOMIZER_ITEMS_H OOT_RANDOMIZER_ITEMS_H

#include <iostream>
#include <cstring>
#include <vector>
#include "chests.h"


namespace OoT_Randomizer {

namespace Randomizer {

struct Item
{
    std::string name;                 /*Name of the item*/
	uint8_t id;                  /*Item number*/
	uint16_t chest_id;           /*Value to override chest data*/
	bool used;                   /*If item has been placed*/
    std::vector<Chest*> unlocks;      /*Chests that this item gives access to*/
    constexpr bool operator<(const Item& item) const {
        return (used == item.used ? unlocks.size() > item.unlocks.size() : used < item.used);
    }
    constexpr bool operator==(const Item &item) const { return id == item.id; }
};


}

}
#endif
