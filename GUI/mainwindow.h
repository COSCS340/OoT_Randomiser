#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QFutureWatcher>
#include <random>
#include <memory>
#include <functional>
namespace Ui {
class MainWindow;
}

namespace OoT_Randomizer {

namespace Ui {
class OffThreadRandomizer;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    void setSeed(std::uint64_t seed);

    ~MainWindow();

public slots:
    void on_progress(QString msg, int progress);

    void on_randomizeColorsCheckBox_clicked(bool checked);

    void on_randomizeChestContentsCheckBox_clicked(bool checked);

private slots:
    void on_exitWithoutSaving_released();

    void on_rNGSeedLineEdit_editingFinished();

    void on_randomizeRequirementsCheckBox_clicked(bool checked);

    void on_seedRNGButton_pressed();

    void on_exitWithoutSaving_pressed();

    void on_selectInputFile_pressed();

    void onRunComplete();

    void onOutputfilenameChosen(QString str);

    void on_selectOutputFile_clicked(bool checked);

    void on_runButton_released();

private:
    ::Ui::MainWindow *ui;
    std::mt19937_64 m_prng;
    bool m_shouldRandomizeColors;
    bool m_shouldRandomizeChestContents;
    bool m_shouldRandomizeRequirements;
    std::random_device m_random_device;
    QString m_fName, m_ofName;
    QFileDialog *m_dialog;
    std::unique_ptr<OffThreadRandomizer> m_randomizer;
    std::unique_ptr<QFutureWatcher<QString> > m_future;
};

}

}

#endif // MAINWINDOW_H
