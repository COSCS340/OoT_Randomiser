#ifndef OOT_RANDOMIZER_ITEMS_H
#define OOT_RANDOMIZER_ITEMS_H

#include <iostream>
#include <cstring>
#include <vector>
#include <array>
#include <algorithm>

namespace OoT_Randomizer {

namespace Randomizer {
void randomize_file(std::vector<unsigned char> &data);

int real_main(int argc, char **argv);
constexpr std::size_t NUM_ITEMS = 14;
constexpr std::size_t NUM_CHESTS = 28;
struct Chest
{
    std::string name;            /*Name of chest location*/
    unsigned int offset;    /*Location of the chest in game data*/
    unsigned short flags;   /*Chest type and Chest flag*/
    bool available;         /*If the chest is available to place items in*/
    bool used;              /*If the chest has been used already*/
    bool operator<(const Chest& c) {return(this->available > c.available);}
};

struct Item
{
    bool used;                      /*If item has been placed*/
    std::string name;               /*Name of the item*/
    unsigned char id;               /*Item number*/
    unsigned short chest_id;        /*Value to override chest data*/
    std::vector<Chest*> unlocks;    /*Chests that this item gives access to*/
    bool operator<(const Item&) const;
    bool operator==(const Item&) const;
};

struct Args
{
    int num_progression;
    std::array<Item, NUM_ITEMS> items;
    std::array<Item, 3> combo;
    void sortItems();
    void makeCombo();

    std::array<Chest, 28> chests;
    int chests_available;
    void sortChests();

    void randomise();
    Args();
};

}
}
#endif
