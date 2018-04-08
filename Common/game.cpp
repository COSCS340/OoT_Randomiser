#include <QFile>
#include <QString>

#include <Common/game.hpp>
#include <Randomiser/args.h>
#include <colors/custom_colors.h>

namespace OoT_Randomizer {
namespace Common {

void randomize(std::vector<unsigned char> &data, bool randomize_chests, bool randomize_colors, std::uint64_t seed) {
    if (randomize_chests) {
        OoT_Randomizer::Randomizer::Args args;
        args.randomize(data);
    }
    if (randomize_colors) {
        //OoT_Randomizer::CustomColors::custom_colors(data);
    }
}

QString Execute(QString const &in_file, QString const &out_file, bool randomize_chests, bool randomize_colors, std::uint64_t seed, std::function<void(QString, int)> *cb) {
    auto data = std::vector<unsigned char>(GAME_SIZE);
    {
        QFile input_file(in_file);
        if (!input_file.open(QIODevice::ReadOnly)) {
            return QStringLiteral("Cannot open input file %1: %2").arg(in_file, input_file.errorString());
        }
        for (std::size_t i = 0, new_max{0}; i < GAME_SIZE; i = new_max) {
            new_max = std::min(std::size_t{i + (1UL << 14)}, GAME_SIZE);
            input_file.read(reinterpret_cast<char*>(data.data()) + i, qint64(new_max - i));

            if (cb) {
                int size = int(qulonglong(new_max)*100ULL/GAME_SIZE);
                cb->operator()(QStringLiteral("Reading input file\u2026 %1 complete").arg(size), size);
            }
        }
    }
    if (cb) {
        cb->operator()(QStringLiteral("Randomizing\u2026"), 0);
    }
    randomize(data, randomize_chests, randomize_colors, seed);
    if (cb) {
        cb->operator()(QStringLiteral("Randomizing\u2026 complete."), 100);
    }
    {
        QFile output_file(out_file);
        if (!output_file.open(QIODevice::WriteOnly)) {
            return QStringLiteral("Cannot open output file %1: %2").arg(in_file, output_file.errorString());
        }
        for (std::size_t i = 0, new_max{0}; i < GAME_SIZE; i = new_max) {
            new_max = std::min(std::size_t{i + (1UL << 14)}, GAME_SIZE);
            output_file.write(reinterpret_cast<char*>(data.data()) + i, qint64(new_max - i));

            if (cb) {
                int size = int(qulonglong(new_max)*100ULL/GAME_SIZE);
                cb->operator()(QStringLiteral("Writing output file\u2026 %1 complete").arg(size), size);
            }
        }
    }
    return QStringLiteral("");
}
}
}
