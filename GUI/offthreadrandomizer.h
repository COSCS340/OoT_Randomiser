#ifndef OFFTHREADRANDOMIZER_H
#define OFFTHREADRANDOMIZER_H

#include <QObject>
#include "mainwindow.h"
namespace OoT_Randomizer {

namespace Ui {
class OffThreadRandomizer : public QObject
{
    Q_OBJECT
public:
    void operator()(QString str, quint32 progress);
    static QString ExecuteOnFile(MainWindow *target, QString fname, QString ofname, bool randomizeChests, bool randomizeColors);

signals:
    void ReportProgress(QString str, quint32 progress);
public slots:
private:
    QString Execute(QString fname, QString ofname, bool randomizeChests, bool randomizeColors);
    explicit OffThreadRandomizer(QObject *parent = nullptr);

};

}

}

#endif // OFFTHREADRANDOMIZER_H
