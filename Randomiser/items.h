#ifndef ITEMS_H
#define ITEMS_H

#include <iostream>
#include <cstring>
#include <vector>
#include <array>
#include <algorithm>

#define NUM_ITEMS 14
#define NUM_CHESTS 28

namespace OoT_Randomizer {

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
    bool operator<(const Item&);
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

Args::Args() : num_progression(0), items{{
{false, "Fairy Slingshot", 0x05, 0x00a0, {}},
{false, "Boomerang", 0x06, 0x00c0, {}},
{false, "Lens of Truth", 0x0a, 0x0140, {}},
{false, "Ocarina of Time", 0x0c, 0x0180, {}},
{false, "Empty Bottle", 0x0f, 0x01E0, {}},
{false, "Empty Bottle", 0x0f, 0x01E0, {}},
{false, "Empty Bottle", 0x0f, 0x01E0, {}},
{false, "Empty Bottle", 0x0f, 0x01E0, {}},
{false, "Kokiri Sword", 0x27, 0x04e0, {}},
{false, "Deku Shield", 0x29, 0x0520, {}},
{false, "Hylian Shield", 0x2A, 0x0540, {}},
{false, "Bomb Bag", 0x32, 0x0640, {}},
{false, "Golden Scale", 0x38, 0x0700, {}},
{false, "Giant Wallet", 0x46, 0x08C0, {}},
}}, combo{items[0], items[1], items[2]}, chests{{
{"Mido's House 3", 0x02f7b0ba, 0x5903, true, false},
{"Mido's House 2", 0x02f7b0aa, 0x5982, true, false},
{"Mido's House 1", 0x02f7b09a, 0x59A1, true, false},
{"Mido's House 0", 0x02f7b08a, 0x59A0, true, false},
{"Kokiri Sword Chest", 0x020a6142, 0x04E0, true, false},
{"DT Map Chest", 0x024a7138, 0x0823, true, false},
{"DT Slingshot Chest", 0x024c20b8, 0x00a1, true, false},
{"DT S Heart Chest", 0x024c20c8, 0x5905, true, false},
{"DT Basement Chest", 0x024c8158, 0x5904, true, false},
{"DT Compass Chest", 0x025040c8, 0x0802, true, false},
{"DT C Heart Chest", 0x025040d8, 0x5906, true, false},
{"DC Map Chest", 0x01f2819e, 0x0828, false, false},
{"DC Deku Shield Chest", 0x01f281ce, 0x552a, false, false},
{"DC Bomb Bag Chest", 0x01f890ce, 0x0644, false, false},
{"DC Red Rupee Chest", 0x01f890de, 0x59c6, false, false},
{"DC Compass Chest", 0x01faf0aa, 0x0805, false, false},
{"JJ Compass Chest", 0x02796000, 0xb804, false, false},
{"JJ Map Chest", 0x02780000, 0x1822, false, false},
{"JJ Bomerang Chest", 0x0278a000, 0x10c1, false, false},
{"Fairy Fountain Grave", 0x0328b096, 0x5540, true, false},
{"Redead Grave", 0x02d0a056, 0xa7c0, false, false},
{"Royal Family Tomb", 0x0332d0ea, 0x8020, false, false},
{"GC Rock Room 200R", 0x0227c23a, 0x5ac0, false, false},
{"GC Rock Room Right", 0x0227c24a, 0x5aa1, false, false},
{"GC Rock Room Left", 0x0227c25a, 0x5aa2, false, false},
{"Zora's Domian PoH Chest", 0x02103166, 0xb7c0, false, false},
{"Redead Grotto", 0x026cf076, 0x7aca, false, false},
{"Death Mountian Trail", 0x0223c3ca, 0x5aa1, false, false},
}}, chests_available(28) {
    std::sort(chests.begin(), chests.end());
}


  void Args::makeCombo()
{
}

void Args::sortItems()
{
    std::sort(items.begin(), items.end());
}

bool Item::operator<(const Item& i)
{
    if(used < i.used)
        return true;
    else if(used > i.used)
        return false;
    else
        return unlocks.size() > i.unlocks.size();
}

bool Item::operator==(const Item& i) const
{
    return(id == i.id);
}
}
#endif
