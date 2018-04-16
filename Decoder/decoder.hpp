#ifndef OOT_RANDOMIZER_DECODER_HPP
#define OOT_RANDOMIZER_DECODER_HPP

#include <vector>
#include <cstdint>

namespace OoT_Randomizer {
namespace Decoder {

bool loadAndDecodeFile(const std::vector<unsigned char> &in_buf, std::vector<unsigned char> &buf);

}

}

#endif // OOT_RANDOMIZER_DECODER_HPP
