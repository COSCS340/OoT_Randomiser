#include <memory>

#include <QThread>

#include "offthreadrandomizer.h"
#include <Common/game.hpp>
namespace OoT_Randomizer {
namespace Ui {
OffThreadRandomizer::OffThreadRandomizer(bool randomizeChests, bool randomizeColors) : QObject(nullptr), randomizeChests(randomizeChests), randomizeColors(randomizeColors)
{

}

void OffThreadRandomizer::operator()(QString str, quint32 progress) {
    emit ReportProgress(str, progress);
}


/**
 * @brief ExecuteOnFile
 * @param fname The filename to open.
 * @param ofname The output file name.
 * @param randomizeChests Should we randomize chests?
 * @param randomizeColors Should we randomize colors?
 * @return an error message, or the empty string if there was no error.
 */
QString OffThreadRandomizer::Execute(QString fname, QString ofname) {
    std::function<void(QString, int)> cb{std::reference_wrapper<OffThreadRandomizer>{*this}};
    return Common::Execute(fname, ofname, randomizeChests, randomizeColors, 0, &cb);
}

}

}
