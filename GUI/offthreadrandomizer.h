#ifndef OFFTHREADRANDOMIZER_H
#define OFFTHREADRANDOMIZER_H

#include <QObject>
#include <memory>

#include "mainwindow.h"
namespace OoT_Randomizer {

namespace Ui {
class OffThreadRandomizer : public QObject
{
    Q_OBJECT
public:
    explicit OffThreadRandomizer(QObject *parent = nullptr);

    void operator()(QString str, quint32 progress);
    static QString ExecuteOnFile(std::shared_ptr<OffThreadRandomizer> randomizer, QString fname, QString ofname, bool randomizeChests, bool randomizeColors);

signals:
    void ReportProgress(QString str, quint32 progress);
public slots:
private:
    QString Execute(QString fname, QString ofname, bool randomizeChests, bool randomizeColors);
};

}

}

#endif // OFFTHREADRANDOMIZER_H
