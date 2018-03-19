#ifndef OOT_RANDOMIZER_GAME_HPP
#define OOT_RANDOMIZER_GAME_HPP

#include <cstdint>
#include <vector>
#include <functional>

#include <QString>

namespace OoT_Randomizer {
namespace Common {
void randomize(std::vector<unsigned char> &ROM, bool randomize_chests, bool randomize_colors, std::uint64_t seed);
static constexpr std::size_t GAME_SIZE = 67108864;
static constexpr bool DEBUG = true;
QString Execute(const QString &input_file, const QString &output_file, bool randomize_chests, bool randomize_colors, std::uint64_t seed, std::function<void(QString, int)> *cb = nullptr);
}
}

#endif // OOT_RANDOMIZER_GAME_HPP
