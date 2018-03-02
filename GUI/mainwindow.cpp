#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <random>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), prng(), shouldRandomizeColors(false), shouldRandomizeChestContents(false), shouldRandomizeRequirements(false),
    random_device()
{
    ui->setupUi(this);
    ui->rNGSeedLineEdit->setValidator(new QIntValidator);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_exitWithoutSaving_released()
{
    QCoreApplication::quit();
}

void MainWindow::on_rNGSeedLineEdit_editingFinished()
{
    bool isOkay;
    unsigned long long seedValue = ui->rNGSeedLineEdit->text().toULongLong(&isOkay, 10);
    if (!isOkay) return;
    prng.seed(seedValue);
}

void MainWindow::on_randomizeColorsCheckBox_clicked(bool checked)
{
    shouldRandomizeColors = checked;
}

void MainWindow::on_randomizeChestContentsCheckBox_clicked(bool checked)
{
    shouldRandomizeChestContents = checked;
}

void MainWindow::on_randomizeRequirementsCheckBox_clicked(bool checked)
{
    shouldRandomizeRequirements = checked;
}

void MainWindow::on_seedRNGButton_pressed()
{
    ui->rNGSeedLineEdit->setText(QString::fromStdString(std::to_string(int(random_device()))));
}
