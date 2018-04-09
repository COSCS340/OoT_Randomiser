#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdint>
#include <set>
#include <array>
#include <vector>
#include <QByteArray>
#include <QCoreApplication>
#include <QFile>

void ErrorCheck(int, char**);

#include "args.h"
#include "chests.h"
#include "items.h"
namespace R = OoT_Randomizer::Randomizer;
#if 0

void R::Args::randomise()
{
    std::size_t i = 0;
    std::size_t j, rChest, rItem;

    while(chests_available > 0)
    {
        //Pick a random chest to put stuff in
        rChest = rand() % chests_available;

        //If it's the last available chest, and there are still progression items
        //then force a progression item to be placed, else pick a random item
        if(chests_available == 1 and num_progression != 0)
            rItem = rand() % num_progression;
        else
            rItem = rand() % (NUM_ITEMS-i);

        //Combine the item's chest value, and the chest's id value to place the
        //item in the chest, then set some flags for the next iteration to use
        chests[rChest]->flags = chests[rChest]->flags & 0xF01F;
        chests[rChest]->flags = chests[rChest]->flags | items[rItem]->chest_id;
        chests[rChest]->available = false;
        combo.push_back(items[rItem]->id);
        chests[rChest]->used = true;
        items[rItem]->used = true;
        chests_available--;

        //If the item was a progression item, unlock the chests in it's unlocks vector
        if(items[rItem]->unlocks.size() != 0)
        {
            num_progression--;

            for(j = 0; j < items[rItem]->unlocks.size(); j++)
            {
                if(items[rItem]->unlocks[j]->used)
                    continue;
                if(!items[rItem]->unlocks[j]->available)
                {
                    items[rItem]->unlocks[j]->available = true;
                    chests_available++;
                }
            }
        }

        printf("%s in %s\n", items[rItem]->name.c_str(), chests[rChest]->name.c_str());
        checkCombo(items[rItem]->id);

        //Sort the chests and items again
        sortChests();
        sortItems();
        i++;
    }
}
#endif



/*
void actorSetup(uint8_t* data)
{
    //Move Mido (X, Y, Z)
    data[x] = 0x0000;
    data[x] = 0x0010;
    data[x] = 0x0000;

    //Move other kokiri kid
    data[x] = 0x0000;
    data[x] = 0x0010;
    data[x] = 0x0000;

    //Open Death Mountian gate
    data[x] = 0xff9c;
    data[x] = 0x019a;
    data[x] = 0xfa9c;

    //Swap Silver Gauntlets with Green Rupee
    //Unimplemented, waiting to figure out progressive upgrades
}
*/

/*
    Function: ErrorCheck
    Purpose: All of the error checking in one function to make it pretty
    Paramaters: Argc and Argv
    Returns: N/A
*/
