#include "mainwindow.h"
#include <Decoder/crc.h>
#include <QApplication>
#include <QCommandLineParser>
#include <iostream>

#include <Extractor/extract.hpp>
#include <colors/custom_colors.h>
#include <Randomiser/chests.h>
#include <Randomiser/items.h>
#include <Common/game.hpp>

int main(int argc, char *argv[])
{
    OoT_Randomizer_crc_init(); // cannot fail
    QApplication a{argc, argv};
    QCoreApplication::setApplicationName("Ocarina of Time Randomizer");
    QCoreApplication::setApplicationVersion("0.0.1");

    QCommandLineParser parser{};
    parser.setApplicationDescription("Randomizer for Zelda Ocarina of Time game ROMs");
    parser.addPositionalArgument("dest", QCoreApplication::translate("main", "Output file"));
    parser.addVersionOption();
    parser.addHelpOption();
    parser.addPositionalArgument("source", QCoreApplication::translate("main", "Input file"));
    parser.addOptions({
       {"seed",
        QCoreApplication::translate("main", "Sets the seed to <seed> (default: random)"),
        QCoreApplication::translate("main", "seed")},
       {"randomize-colors", QCoreApplication::translate("main", "Randomize colors")},
       {"randomize-chests", QCoreApplication::translate("main", "Randomize chests")},
       {"gui", QCoreApplication::translate("main", "Launch the GUI, even if --randomize-colors or --randomize-chests is passed")},
    });
    parser.process(QCoreApplication::arguments());
    bool randomize_colors = parser.isSet("randomize-colors");
    bool randomize_chests = parser.isSet("randomize-chests");
    bool force_gui = parser.isSet("gui");
    uint64_t seed = 0;
    bool has_seed;
    if ((has_seed = parser.isSet("seed"))) {
        const QString val = parser.value("seed");
        bool okay;
        seed = val.toULongLong(&okay, 0);
        if (!okay) {
            parser.showHelp(1);
        }
    }
    QStringList pos_args = parser.positionalArguments();
    if (force_gui || (!(randomize_chests || randomize_colors)) || pos_args.length() < 2) {
        OoT_Randomizer::Ui::MainWindow w;
        if (has_seed) {
            w.setSeed(seed);
        }
        w.on_randomizeChestContentsCheckBox_clicked(randomize_chests);
        w.on_randomizeColorsCheckBox_clicked(randomize_colors);
        w.show();

        return a.exec();
    } else {
        std::function<void(QString, int)> x = [](QString x, int y) { Q_UNUSED(x); Q_UNUSED(y); };
        QString res = ::OoT_Randomizer::Common::Execute(pos_args.at(0), pos_args.at(1), randomize_chests, randomize_colors, seed, &x);
        if (res.length()) {
            qCritical("Fatal error: %s", qUtf8Printable(res));
            return 1;
        }
    }
}
