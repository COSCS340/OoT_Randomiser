#include <QFile>
#include <QString>

#include <Common/game.hpp>
#include <Randomiser/args.h>
#include <colors/custom_colors.h>
#include <Decoder/decoder.hpp>
#include <Decoder/crc.h>

namespace OoT_Randomizer {
using Decoder::loadAndDecodeFile;
namespace Common {
constexpr size_t COMPRESSED_GAME_SIZE = GAME_SIZE / 2;

void randomize(std::vector<unsigned char> &data, bool randomize_chests, bool randomize_colors, std::uint64_t seed) {
    if (randomize_chests) {
        OoT_Randomizer::Randomizer::Args args{seed};
        args.randomize(data);
    }
    if (randomize_colors) {
        OoT_Randomizer::CustomColors::custom_colors(data);
    }
}

QString Execute(QString const &in_file, QString const &out_file, bool randomize_chests, bool randomize_colors, std::uint64_t seed, std::function<void(QString, int)> *cb) {
    auto data = std::vector<unsigned char>(COMPRESSED_GAME_SIZE);
    auto compressed_data = std::vector<unsigned char>(COMPRESSED_GAME_SIZE);
    static_assert(GAME_SIZE == 1 << 26, "GAME_SIZE must equal 1 << 26");
    static_assert(alignof (uint32_t) <= 4, "uint32_t must have an alignment <= 4");
    static_assert(sizeof (uint32_t) == 4, "uint32_t must have size 4");
    {
        QFile input_file(in_file);
        if (!input_file.open(QIODevice::ReadOnly)) {
            return QStringLiteral("Cannot open input file %1: %2").arg(in_file, input_file.errorString());
        }
        for (std::size_t i = 0, new_max{0}; i < COMPRESSED_GAME_SIZE; i = new_max) {
            new_max = std::min(std::size_t{i + (1UL << 14)}, COMPRESSED_GAME_SIZE);
            auto bytes_to_read = qint64(new_max - i);
            qint64 bytes_read = input_file.read(reinterpret_cast<char*>(compressed_data.data()) + i, bytes_to_read);
            if (input_file.error()) {
                return input_file.errorString();
            }

            if (bytes_read > bytes_to_read) {
                abort();
            } else if (bytes_read < bytes_to_read) {
                if (0 == bytes_read) {
                    return QStringLiteral("Preamature end of file reading from %1").arg(in_file);
                } else {
                    new_max -= std::size_t(bytes_to_read - bytes_read);
                }
            }

            if (cb) {
                int size = int(qulonglong(new_max)*100ULL/COMPRESSED_GAME_SIZE);
                cb->operator()(QStringLiteral("Reading input file\u2026 %1 complete").arg(size), size);
            }
        }
    }
    loadAndDecodeFile(compressed_data, data);

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
            return QStringLiteral("Cannot open output file %1: %2").arg(out_file, output_file.errorString());
        }
        for (std::size_t i = 0, new_max{0}; i < GAME_SIZE; i = new_max) {
            new_max = std::min(std::size_t{i + (1UL << 14)}, GAME_SIZE);
            qint64 bytes_to_write = qint64(new_max - i);
            qint64 bytes_written = output_file.write(reinterpret_cast<char*>(data.data()) + i, bytes_to_write);
            if (output_file.error()) {
                return QStringLiteral("Error writing to %1: %2").arg(out_file, output_file.errorString());
            }
            if (bytes_to_write < bytes_written)
                abort();
            else if (bytes_to_write > bytes_written) {
                new_max -= std::size_t(bytes_to_write - bytes_written);
            }

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
