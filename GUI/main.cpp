#include "mainwindow.h"
#include <QApplication>
#include <iostream>

#include <Extractor/extract.hpp>
#include <colors/custom_colors.h>
#include <Randomiser/items.h>

int main(int argc, char *argv[])
{
    if (argc >= 2) try {
        if (!strcmp(argv[1], "randomize"))
            return OoT_Randomizer::Randomizer::real_main(argc - 1, argv + 1);
        else if (!strcmp(argv[1], "randomize-colors"))
            return OoT_Randomizer::CustomColors::real_main(argc - 1, argv + 1);
        else if (!strcmp(argv[1], "gui"))
            ;
        else if (!strcmp(argv[1], "extract"))
            return OoT_Randomizer::Extract::real_main(argc - 1, argv + 1);
        else {
            std::cerr << R"(This is a randomizer for the Zelda Ocarina of Time game ROM.

Usage:

oot-randomizer [gui]
    displays the GUI
oot-randomizer --help
    display this message
oot-randomizer randomize RANDOMIZE_ARGS
    Randomize the chests in the input file.
oot-randomizer randomize-colors RANDOMIZE_COLORS_ARGS
    Randomize the colors in the input file.
)";
            return strcmp(argv[1], "--help") ? 1 : 0;
        }
    } catch (std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    QApplication a(argc, argv);
    OoT_Randomizer::Ui::MainWindow w;
    w.show();

    return a.exec();
}
