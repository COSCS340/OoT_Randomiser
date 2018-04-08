#ifndef OOT_RANDOMIZER_ARGS_H
#define OOT_RANDOMIZER_ARGS_H

#include <cstdint>
#include <vector>
#include <array>
#include <random>
namespace OoT_Randomizer {

namespace Randomizer {


namespace {
const constexpr size_t GAME_SIZE = 67108864L;
const constexpr bool DEBUG = true;
const constexpr size_t NUM_ITEMS = 29;
const constexpr size_t NUM_CHESTS = 29;
const constexpr size_t NUM_COMBOS = 8;
}
struct Chest;
struct Item;
struct Args
{
    // If this throws std::bad_alloc, we are screwed, as Qt cannot recover from
    // OOM anyway.  Just abort.
    Args() noexcept;
    ~Args();
    void randomize(::std::vector<uint8_t> &vec);
private:

    void makeItems();
    void sortItems();
    void makeCombo();
    void makeChests();
    void sortChests();
    std::array<Chest*, NUM_CHESTS> chests;
    std::array<Chest*, NUM_COMBOS> combos;
    std::array<Item*, NUM_ITEMS>items;
    int num_progression;
    int chests_available;
    std::mt19937_64 engine;
    std::vector<uint8_t> combo;
    void randomise();
    void checkCombo(uint8_t);
};

}

}

#endif // OOT_RANDOMIZER_ARGS_H
