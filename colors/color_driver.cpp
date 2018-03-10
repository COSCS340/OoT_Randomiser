#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include "custom_colors.h"

#define GAME_SIZE 67108864

int main( int argc, char** argv) {

    try {
        std::vector<unsigned char> game(GAME_SIZE);
        std::ofstream output;
        {
            std::ifstream input;
            input.open(argv[1], std::ios::binary);
            input.read(reinterpret_cast<char*>(game.data()), GAME_SIZE);
            if (input.gcount() < GAME_SIZE) {
                throw std::runtime_error("input file too short");
            }
            input.close();
        }

        custom_colors(game);

        output.open("newzoot.z64", std::ios::binary);
        output.write(reinterpret_cast<const char*>(game.data()), GAME_SIZE);

        return 0;
    } catch (std::runtime_error &e) {
        std::cerr << e.what() << '\n';
        return 1;
    }
}
