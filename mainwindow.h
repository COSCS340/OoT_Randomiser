#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <random>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_exitWithoutSaving_released();

    void on_rNGSeedLineEdit_editingFinished();

    void on_randomizeColorsCheckBox_clicked(bool checked);

    void on_randomizeChestContentsCheckBox_clicked(bool checked);

    void on_randomizeRequirementsCheckBox_clicked(bool checked);

    void on_seedRNGButton_pressed();

private:
    Ui::MainWindow *ui;
    std::mt19937_64 prng;
    bool shouldRandomizeColors;
    bool shouldRandomizeChestContents;
    bool shouldRandomizeRequirements;
    std::random_device random_device;
};

#endif // MAINWINDOW_H
