#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <array>
#include <vector>
namespace OoT_Randomizer {

namespace CustomColors {

int real_main(int argc, char **argv);
void custom_colors(std::vector<unsigned char> &game);
class Gear {
public:
    std::string name;
    unsigned int offset;
    unsigned char R;
    unsigned char G;
    unsigned char B;
};

struct mycolor {
    std::uint8_t R, G, B, a;
    std::uint32_t addr;
    const char *name;
};
namespace {
inline std::array<mycolor, 6> make_navi() {
    std::array<mycolor, 6> navi{{
            {0xff, 0xff, 0xff, 0xff, 0xb5e184, "normal"},
            {0x00, 0x00, 0xff, 0x00, 0xb5e188, "npc"},
            {0x00, 0xff, 0x00, 0xff, 0xb5e18c, "enemy"},
            {0x96, 0x96, 0xff, 0xff, 0xb5e194, "sign_gstone"},
            {0xff, 0xff, 0x00, 0xff, 0xb5e19c, "check_spots"},
            {0x00, 0xff, 0x00, 0xff, 0xb5e1ac, "boss"},
                                }};
    return navi;
}

inline std::array<Gear, 5> make_color_list() {
    return {{
            {"Kokiri Tunic", 0xb6da38, 0x1e, 0x69, 0x1b},
            {"Goron Tunic", 0xb6da3b, 0x64, 0x14, 0x00},
            {"Zora Tunic", 0xb6da3e, 0x00, 0x3c, 0x64},
            {"Silver Gauntlets", 0xb6da44, 0xff, 0xff, 0xff},
            {"Golden Gauntlets", 0xb6da47, 0xfe, 0xcf, 0x0f},
        }};
}
}

}

}


