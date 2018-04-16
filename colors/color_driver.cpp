#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include "custom_colors.h"

#define GAME_SIZE 67108864

namespace OoT_Randomizer {

namespace CustomColors {
// create lists and modify game data
void custom_colors(std::vector<unsigned char> &game) {
    const std::size_t game_size = game.size();
    if (game_size < 4) {
        throw std::runtime_error("Game length too short");
    }
    for (const auto &gear: make_color_list()) {
        const std::size_t offset = gear.offset;
        if (offset >= game_size - 2) {
            throw std::runtime_error("Offset out of range for game");
        }
        game.at(offset) = gear.R;
        game.at(offset+1) = gear.G;
        game.at(offset+2) = gear.B;
    }

    for (const auto &navi: make_navi()) {
        const std::size_t offset = navi.addr;
        if (offset >= game_size - 4) {
            throw std::runtime_error("Navi offset out of range for game");
        }
        game.at(offset) = navi.R;
        game.at(offset + 1) = navi.G;
        game.at(offset + 2) = navi.B;
        game.at(offset + 3) = navi.a;
    }
}

int real_main( int argc, char** argv) {
    (void)argc;
    try {
        std::vector<unsigned char> game(GAME_SIZE);
        {
            std::ifstream input;
            input.exceptions(std::ios_base::badbit|std::ios_base::failbit|std::ios_base::eofbit);
            input.open(argv[1], std::ios::binary);
            input.read(reinterpret_cast<char*>(game.data()), GAME_SIZE);
            if (input.gcount() < GAME_SIZE) {
                throw std::runtime_error("input file too short");
            }
            if (input.gcount() > GAME_SIZE) {
                throw std::logic_error("internal error");
            }
        }

        custom_colors(game);
        {
            std::ofstream output;
            output.exceptions(std::ios_base::badbit|std::ios_base::failbit|std::ios_base::eofbit);
            output.open("newzoot.z64", std::ios::binary);
            output.write(reinterpret_cast<const char*>(game.data()), GAME_SIZE);
        }
        return 0;
    } catch (std::runtime_error &e) {
        std::cerr << e.what() << '\n';
        return 1;
    }
}

}

}
