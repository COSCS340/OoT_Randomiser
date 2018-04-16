#ifndef OOT_RANDOMIZER_OFFTHREADRANDOMIZER_H
#define OOT_RANDOMIZER_OFFTHREADRANDOMIZER_H

#include <QObject>
#include <memory>

#include "mainwindow.h"
namespace OoT_Randomizer {

namespace Ui {
class OffThreadRandomizer : public QObject
{
    Q_OBJECT
public:
    QString Execute(QString fname, QString ofname);
    explicit OffThreadRandomizer(bool randomizeChests, bool randomizeColors);
    void operator()(QString str, quint32 progress);
    //static QString ExecuteOnFile(std::shared_ptr<OffThreadRandomizer> randomizer, QString fname, QString ofname);

signals:
    void ReportProgress(QString str, quint32 progress);
private:
    bool randomizeChests;
    bool randomizeColors;
};

}

}

#endif // OOT_RANDOMIZER_OFFTHREADRANDOMIZER_H
