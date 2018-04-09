#include <cstdint>
#include <ctime>
#include <memory>
#include <vector>
#include <algorithm>

#include <QFile>
#include <QCoreApplication>
#include "args.h"
#include "chests.h"
#include "items.h"
#include "custom_colors.h"
#include <Common/game.hpp>

namespace OoT_Randomizer {

namespace Randomizer {

Args::Args() noexcept : chests{{0}}, combos{{0}}, items{{0}}  {
    makeChests();
    sortChests();
    makeItems();
    sortItems();
    makeCombo();
}

Args::~Args() {
    for (auto &i: chests) {
        delete i;
        i = nullptr;
    }
    for (auto &i: items) {
        delete i;
        i = nullptr;
    }
}

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
    chest->offset = 0x024a7146;
    chest->flags = 0x0823;
    chest->available = true;
    chest->used = false;
    chests[5] = chest;

    //Deku Tree Slingshot Chest
    chest = new Chest;
    chest->name = "DT Slingshot Chest";
    chest->offset = 0x024c20c6;
    chest->flags = 0x00a1;
    chest->available = true;
    chest->used = false;
    chests[6] = chest;

    //Deku Tree Heart Chest (Slingshot room)
    chest = new Chest;
    chest->name = "DT S Heart Chest";
    chest->offset = 0x024c20d6;
    chest->flags = 0x5905;
    chest->available = true;
    chest->used = false;
    chests[7] = chest;

    //Deku Tree Basement Chest
    chest = new Chest;
    chest->name = "DT Basement Chest";
    chest->offset = 0x024c8166;
    chest->flags = 0x5904;
    chest->available = true;
    chest->used = false;
    chests[8] = chest;

    //Deku Tree Compass Chest
    chest = new Chest;
    chest->name = "DT Compass Chest";
    chest->offset = 0x025040d6;
    chest->flags = 0x0802;
    chest->available = true;
    chest->used = false;
    chests[9] = chest;

    //Deku Tree Heart Chest (Compass room)
    chest = new Chest;
    chest->name = "DT C Heart Chest";
    chest->offset = 0x025040e6;
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
    chest->offset = 0x0279608a;
    chest->flags = 0xb804;
    chest->available = false;
    chest->used = false;
    chests[16] = chest;
    combos[2] = chest;

    //JJ Map Chest
    chest = new Chest;
    chest->name = "JJ Map Chest";
    chest->offset = 0x0278e08a;
    chest->flags = 0x1822;
    chest->available = false;
    chest->used = false;
    chests[17] = chest;
    combos[3] = chest;

    //JJ Boomerang Chest
    chest = new Chest;
    chest->name = "JJ Bomerang Chest";
    chest->offset = 0x0278a0ba;
    chest->flags = 0x10c1;
    chest->available = false;
    chest->used = false;
    chests[18] = chest;
    combos[4] = chest;

    //Fairy Fountain Grave
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
    chest->name = "Zora's Domain PoH Chest";
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
    ::std::stable_sort(chests.begin(), chests.end(), [](const Chest *chest1, const Chest *chest2) -> bool { return chest1->available > chest2->available; });
}

void Args::makeCombo()
{
}


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
    ::std::sort(items.begin(), items.end());
}

static constexpr auto GAME_SIZE = OoT_Randomizer::Common::GAME_SIZE;

/*
    Function: checkCombo
    Purpose: Checks for item pairs that can be used to unlock chests
    Paramaters: Item A's id
    Returns: N/A
*/
void Args::checkCombo(uint8_t id)
{
    //Ocarina of Time
    if(id == 0x0C)
    {
        //Bombs
        if(std::find(combo.begin(), combo.end(), 0x32) != combo.end())
        {
            //Zora's Domain Chest
            if(!combos[6]->used and !combos[6]->available)
            {
                combos[6]->available = true;
                chests_available++;
            }
        }

        //Din's Fire
        if(std::find(combo.begin(), combo.end(), 0x5C) != combo.end())
        {
            //Royal Family Tomb Chest
            if(!combos[5]->used and !combos[5]->available)
            {
                combos[5]->available = true;
                chests_available++;
            }
        }

        return;
    }

    //Din's Fire
    if(id == 0x5C)
    {
        //Ocarina of Time
        if(std::find(combo.begin(), combo.end(), 0x0C) != combo.end())
        {
            //Royal Family Tomb Chest
            if(!combos[5]->used and !combos[5]->available)
            {
                combos[5]->available = true;
                chests_available++;
            }
        }
    }

    //Bombs
    if(id == 0x32)
    {
        //Slingshot
        if(std::find(combo.begin(), combo.end(), 0x05) != combo.end())
        {
            //DC small chest (bridge)
            if(!combos[0]->used and !combos[0]->available)
            {
                combos[0]->available = true;
                chests_available++;
            }

            //DC Bomb bag chest
            if(!combos[1]->used and !combos[1]->available)
            {
                combos[1]->available = true;
                chests_available++;
            }

            //DC small chest (boss room)
            if(!combos[7]->used and !combos[7]->available)
            {
                combos[7]->available = true;
                chests_available++;
            }
        }

        //Ocarina of Time
        if(std::find(combo.begin(), combo.end(), 0x0C) != combo.end())
        {
            //Zora's Domain Chest
            if(!combos[6]->used and !combos[6]->available)
            {
                combos[6]->available = true;
                chests_available++;
            }
        }

        //Bottle
        if(std::find(combo.begin(), combo.end(), 0x0F) != combo.end())
        {
            //Zora's Domain Chest
            if(!combos[6]->used and !combos[6]->available)
            {
                combos[6]->available = true;
                chests_available++;
            }
        }

        return;
    }

    //Goron Bracelet
    if(id == 0x54)
    {
        //Slingshot
        if(std::find(combo.begin(), combo.end(), 0x05) != combo.end())
        {
            //DC Bomb bag chest
            if(!combos[1]->used and !combos[1]->available)
            {
                combos[1]->available = true;
                chests_available++;
            }
        }

        return;
    }

    //Slingshot
    if(id == 0x05)
    {
        //Goron Bracelet
        if(std::find(combo.begin(), combo.end(), 0x54) != combo.end())
        {
            //DC Bomb bag chest
            if(!combos[1]->used and !combos[1]->available)
            {
                combos[1]->available = true;
                chests_available++;
            }
        }

        //Bombs
        if(std::find(combo.begin(), combo.end(), 0x32) != combo.end())
        {
            //DC small chest (bridge)
            if(!combos[0]->used and !combos[0]->available)
            {
                combos[0]->available = true;
                chests_available++;
            }

            //DC Bomb bag chest
            if(!combos[1]->used and !combos[1]->available)
            {
                combos[1]->available = true;
                chests_available++;
            }

            //DC small chest (boss room)
            if(!combos[7]->used and !combos[7]->available)
            {
                combos[7]->available = true;
                chests_available++;
            }
        }

        //Bottle
        if(std::find(combo.begin(), combo.end(), 0x0F) != combo.end())
        {
            //JJ Boomerang Chest
            if(!combos[4]->used and !combos[4]->available)
            {
                combos[4]->available = true;
                chests_available++;
            }
        }

        return;
    }

    //Boomerang
    if(id == 0x06)
    {
        //Bottle
        if(std::find(combo.begin(), combo.end(), 0x0F) != combo.end())
        {
            //JJ Compass Chest
            if(!combos[2]->used and !combos[2]->available)
            {
                combos[2]->available = true;
                chests_available++;
            }

            //JJ Map Chest
            if(!combos[3]->used and !combos[3]->available)
            {
                combos[3]->available = true;
                chests_available++;
            }

            //JJ Boomerang Chest
            if(!combos[4]->used and !combos[4]->available)
            {
                combos[4]->available = true;
                chests_available++;
            }
        }

        return;
    }

    //Bottle
    if(id == 0x0F)
    {
        //Boomerang
        if(std::find(combo.begin(), combo.end(), 0x06) != combo.end())
        {
            //JJ Compass Chest
            if(!combos[2]->used and !combos[2]->available)
            {
                combos[2]->available = true;
                chests_available++;
            }

            //JJ Map Chest
            if(!combos[3]->used and !combos[3]->available)
            {
                combos[3]->available = true;
                chests_available++;
            }

            //JJ Boomerang Chest
            if(!combos[4]->used and !combos[4]->available)
            {
                combos[4]->available = true;
                chests_available++;
            }
        }

        //Bombs
        if(std::find(combo.begin(), combo.end(), 0x32) != combo.end())
        {
            //JJ Boomerang Chest
            if(!combos[4]->used and !combos[4]->available)
            {
                combos[4]->available = true;
                chests_available++;
            }
        }

        //Slingshot
        if(std::find(combo.begin(), combo.end(), 0x05) != combo.end())
        {
            //JJ Boomerang Chest
            if(!combos[4]->used and !combos[4]->available)
            {
                combos[4]->available = true;
                chests_available++;
            }
        }

        return;
    }
}
void Args::randomize(::std::vector<unsigned char> &data) {
    // Count available chests and progression items
    for (::std::size_t i = 0; i < NUM_CHESTS; i++)
        if (chests.at(i)->available)
            chests_available++;
    qDebug("Chests available: %d", chests_available);

    for (::std::size_t i = 0; i < NUM_ITEMS; i++)
        if (items.at(i)->unlocks.size() != 0)
            num_progression++;
    qDebug("Num progressions: %d", num_progression);
    // Sort the chests and items
    // Call the randomiser
    randomise();

    // Edit the data with new chest values
    for (const auto *chest : chests) {
        Q_ASSERT(nullptr != chest);
        data.at(chest->offset) = chest->flags >> 8;
        data.at(chest->offset + 1) = chest->flags & 0xFF;
    }
    // Optionally print out chest and item data
    if (DEBUG) {
        printf("Chests:\n");
        for (const auto *chest : chests) {
            Q_ASSERT(nullptr != chest);
            qDebug("Offset: 0x%08x - Flags: 0x%04x - Used: %i\n", chest->offset,
                   chest->flags, chest->used);
        }

        printf("Items:\n");
        for (const auto *item : items)
            qDebug("Id: %02x, Chest_id: %04x\n", item->id, item->chest_id);
    }
}

int real_main(QStringList args) {
    namespace R = OoT_Randomizer::Randomizer;
    ::std::string name;
    unsigned seed;
    if (args.length() < 2 or args.length() > 3) {
        throw ::std::runtime_error("Usage: Randomise [File name] [Seed (Optional)]\n");
    }

    // Get and set the seed
    ::std::srand(::std::time(NULL));
    if (args.length() == 3) {
        bool b;
        const auto i = args.at(2).toUInt(&b, 0);
        if (b) {
            seed = i;
        }
    }
    srand(seed);



    // Read the data from the source ROM
    auto data = ::std::vector<uint8_t>(R::GAME_SIZE);
    QFile file(args.at(1));
    file.open(QIODevice::ReadOnly);
    static_assert(R::GAME_SIZE < INTPTR_MAX, "Game size must not exceed INTPTR_MAX");
    file.read(reinterpret_cast<char*>(data.data()), qint64(data.size()));
    {
        Args arg;
        arg.randomize(data);
    }

    // Write the edited data to a new file
    name = "ZOoTR_";
    name += ::std::to_string(seed);
    name += ".z64";
    {
        QFile output(name.c_str());
        if (!output.open(QIODevice::WriteOnly)) {
            throw ::std::runtime_error(QStringLiteral("Could not open %1: %2").arg(name.c_str(), output.errorString()).toStdString());
        }
        qint64 res = output.write(reinterpret_cast<char*>(data.data()), qint64(data.size()));
        if (res < 0) {
            throw ::std::runtime_error(QStringLiteral("Could not write to %1: %2").arg(name.c_str(), output.errorString()).toStdString());
        } else if (decltype(data)::size_type(res) != data.size()) {
            typedef unsigned long long ulonglong;
            throw ::std::runtime_error(QString().sprintf("Could not write to %s: wrote only %llu bytes (expected %llu)", name.c_str(), ulonglong(res), ulonglong(data.size())).toStdString());
        }
    }

    return 0;
}

void Args::randomise() {
    ::std::size_t i = 0, rItem, rChest;
    while (this->chests_available > 0) {
        // Pick a random chest to put stuff in
        rChest = ::std::size_t(rand() % chests_available);

        // If it's the last available chest, and there are still progression items
        // then force a progression item to be placed, else pick a random item
        if (chests_available == 1 and num_progression != 0)
            rItem = ::std::size_t(rand()) % ::std::size_t(num_progression);
        else
            rItem = ::std::size_t(rand()) % (NUM_ITEMS - i);
        auto *chestRef = chests.at(rChest);
        Q_ASSERT(chestRef);
        auto *itemRef = items.at(rItem);
        Q_ASSERT(itemRef);
        // Combine the item's chest value, and the chest's id value to place the
        // item in the chest, then set some flags for the next iteration to use
        chestRef->flags &= 0xF01F;
        chestRef->flags |= itemRef->chest_id;
        chestRef->available = false;
        chestRef->used = true;
        itemRef->used = true;
        chests_available--;

        // If the item was a progression item, unlock the chests in it's unlocks
        // vector
        if (itemRef->unlocks.size() != 0) {
            num_progression--;

            for (auto *unlock : itemRef->unlocks) {
                if (unlock->used)
                    continue;
                if (!unlock->available) {
                    unlock->available = true;
                    chests_available++;
                }
            }
        }

        qDebug("%s in %s\n", itemRef->name.c_str(), chestRef->name.c_str());
        // Sort the chests and items again
        sortItems();
        i++;
    }
}
#if 0
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

#endif


}

}

int main(int argc, char** argv)
{
    namespace R = OoT_Randomizer::Randomizer;
    R::Args arg;
    FILE* output;
    std::string name;
    uint8_t temp;
    std::size_t i;

    if (!argv[0]) {
        qCritical("NULL argv[0] pointer");
        exit(1);
    }
    const QCoreApplication app{argc, argv};
    const QStringList args = app.arguments();
    if (args.length() < 1 || args.length() > 2) {
        qCritical("must have at least 1 and at most 2 arguments");
        exit(1);
    }
    bool valid;
    unsigned long long seed;
    if (args.length() >= 2) {
        seed = args.at(2).toULongLong(&valid, 0);
        if (!valid) {
            QByteArray x = args.at(2).toUtf8();
            Q_ASSERT(x.length() <= INT_MAX);
            qCritical("bad number %*s", x.length(), x.data());
            exit(1);
        }
    } else {
        seed = 0;
    }
    QFile input{args.at(0)};
    if (!input.open(QIODevice::ReadOnly)) {
        return 1;
    }
    std::vector<uint8_t> vec(R::GAME_SIZE);

    //Read the data from the source ROM
    if (!input.read(reinterpret_cast<char*>(vec.data()), R::GAME_SIZE)) {
        qCritical("Input too short!  Exiting.");
        return 1;
    }

    //Count available chests and progression items
    arg.randomize(vec);

    //Write the edited data to a new file
    name = "ZOoTR_", name += ::std::to_string(seed), name += ".z64";
    {
        QFile output(name.c_str());
        if (!output.open(QIODevice::WriteOnly)) {
            throw ::std::runtime_error(QStringLiteral("Could not open %1: %2").arg(name.c_str(), output.errorString()).toStdString());
        }
        qint64 res = output.write(reinterpret_cast<char*>(vec.data()), qint64(vec.size()));
        if (res < 0) {
            throw ::std::runtime_error(QStringLiteral("Could not write to %1: %2").arg(name.c_str(), output.errorString()).toStdString());
        } else if (decltype(vec)::size_type(res) != vec.size()) {
            typedef unsigned long long ulonglong;
            throw ::std::runtime_error(QString().sprintf("Could not write to %s: wrote only %llu bytes (expected %llu)", name.c_str(), ulonglong(res), ulonglong(vec.size())).toStdString());
        }
    }

    return(0);
}
