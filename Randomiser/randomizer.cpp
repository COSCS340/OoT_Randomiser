#include <cstdint>
#include <ctime>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

#include <QFile>

#include "items.h"
#include <Common/game.hpp>

namespace OoT_Randomizer {

namespace Randomizer {

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
}}, chests_available(0) {
    std::sort(chests.begin(), chests.end());
}


void Args::makeCombo()
{
}

void Args::sortItems()
{
    std::sort(items.begin(), items.end());
}

bool Item::operator<(const Item& i) const
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
    return id == i.id;
}

static constexpr auto GAME_SIZE = OoT_Randomizer::Common::GAME_SIZE;
static constexpr auto DEBUG = OoT_Randomizer::Common::DEBUG;

void randomize_file(std::vector<unsigned char> &data) {
    Args arg;

    // Count available chests and progression items
    for (std::size_t i = 0; i < NUM_CHESTS; i++)
      if (arg.chests[i].available)
        arg.chests_available++;

    for (std::size_t i = 0; i < OoT_Randomizer::Randomizer::NUM_ITEMS; i++)
      if (arg.items[i].unlocks.size() != 0)
        arg.num_progression++;

    // Sort the chests and items
    // Call the randomiser
    arg.randomise();

    // Edit the data with new chest values
    for (const auto &chest : arg.chests) {
      data.at(chest.offset) = chest.flags >> 8;
      data.at(chest.offset + 1) = chest.flags;
    }
    // Optionally print out chest and item data
    if (DEBUG) {
      printf("Chests:\n");
      for (const auto &chest : arg.chests)
        printf("Offset: 0x%08x - Flags: 0x%04x - Used: %i\n", chest.offset,
               chest.flags, chest.used);

      printf("Items:\n");
      for (const auto &item : arg.items)
        printf("Id: %02x, Chest_id: %04x\n", item.id, item.chest_id);
    }

}
int real_main(int argc, char **argv) {
  std::string name;
  uint32_t seed;

  if (argc < 2 or argc > 3)
    throw std::runtime_error("Usage: Randomise [File name] [Seed (Optional)]\n");

  // Get and set the seed
  std::srand(std::time(NULL));
  (argc == 3) ? seed = atoi(argv[2]) : seed = rand();
  srand(seed);



  // Read the data from the source ROM
  auto data = std::vector<uint8_t>(GAME_SIZE);
  QFile file(argv[1]);
  file.open(QIODevice::ReadOnly);
  static_assert(GAME_SIZE < INTPTR_MAX);
  file.read(reinterpret_cast<char*>(data.data()), qint64(data.size()));

  randomize_file(data);

  // Write the edited data to a new file
  name = "ZOoTR_";
  name += std::to_string(seed);
  name += ".z64";
  {
    QFile output(name.c_str());
    if (!output.open(QIODevice::WriteOnly)) {
      throw std::runtime_error(QStringLiteral("Could not open %1: %2").arg(name.c_str(), output.errorString()).toStdString());
    }
    qint64 res = output.write(reinterpret_cast<char*>(data.data()), qint64(data.size()));
    if (res < 0) {
      throw std::runtime_error(QStringLiteral("Could not write to %1: %2").arg(name.c_str(), output.errorString()).toStdString());
    } else if (decltype(data)::size_type(res) != data.size()) {
        typedef unsigned long long ulonglong;
        throw std::runtime_error(QString().sprintf("Could not write to %s: wrote only %llu bytes (expected %llu)", name.c_str(), ulonglong(res), ulonglong(data.size())).toStdString());
    }
  }

  return (0);
}

void Args::randomise() {
  std::size_t i = 0, rItem;
  int rChest;

  while (this->chests_available > 0) {
    // Pick a random chest to put stuff in
    rChest = rand() % chests_available;

    // If it's the last available chest, and there are still progression items
    // then force a progression item to be placed, else pick a random item
    if (chests_available == 1 and num_progression != 0)
      rItem = std::size_t(rand()) % num_progression;
    else
      rItem = std::size_t(rand()) % (NUM_ITEMS - i);
    auto &chestRef = chests.at(rChest);
    auto &itemRef = items.at(rItem);
    // Combine the item's chest value, and the chest's id value to place the
    // item in the chest, then set some flags for the next iteration to use
    chestRef.flags &= 0xF01F;
    chestRef.flags |= itemRef.chest_id;
    chestRef.available = false;
    chestRef.used = true;
    itemRef.used = true;
    chests_available--;

    // If the item was a progression item, unlock the chests in it's unlocks
    // vector
    if (itemRef.unlocks.size() != 0) {
      num_progression--;

      for (const auto &unlock : itemRef.unlocks) {
        if (unlock->used)
          continue;
        if (!unlock->available) {
          unlock->available = true;
          chests_available++;
        }
      }
    }

    printf("%s in %s\n", itemRef.name.c_str(), chestRef.name.c_str());
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
