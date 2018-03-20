#include <QThread>

#include "offthreadrandomizer.h"
#include <Common/game.hpp>
namespace OoT_Randomizer {
namespace Ui {
OffThreadRandomizer::OffThreadRandomizer(QObject *parent) : QObject(parent)
{

}

void OffThreadRandomizer::operator()(QString str, quint32 progress) {
    emit ReportProgress(str, progress);
}

QString OffThreadRandomizer::ExecuteOnFile(MainWindow *target, QString fname, QString ofname, bool randomizeChests, bool randomizeColors) {
    OffThreadRandomizer randomizer;
    connect(&randomizer, &OffThreadRandomizer::ReportProgress, target, &MainWindow::on_progress, Qt::QueuedConnection);
    return randomizer.Execute(fname, ofname, randomizeChests, randomizeColors);
}

/**
 * @brief ExecuteOnFile
 * @param fname The filename to open.
 * @param ofname The output file name.
 * @param randomizeChests Should we randomize chests?
 * @param randomizeColors Should we randomize colors?
 * @return an error message, or the empty string if there was no error.
 */
QString OffThreadRandomizer::Execute(QString fname, QString ofname, bool randomizeChests, bool randomizeColors) {
    std::function<void(QString, int)> cb{std::reference_wrapper<OffThreadRandomizer>{*this}};
    return Common::Execute(fname, ofname, randomizeChests, randomizeColors, 0, &cb);
}

}

}
