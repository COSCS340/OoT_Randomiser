#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <random>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), m_prng(), m_shouldRandomizeColors(false),
    m_shouldRandomizeChestContents(false), m_shouldRandomizeRequirements(false),
    m_random_device()
{
    ui->setupUi(this);
    ui->rNGSeedLineEdit->setValidator(new QIntValidator);
    ui->inputFileName->setReadOnly(true);
    this->setWindowTitle(tr("Ocarina of Time Randomizer"));
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
    m_prng.seed(seedValue);
}

void MainWindow::on_randomizeColorsCheckBox_clicked(bool checked)
{
    m_shouldRandomizeColors = checked;
}

void MainWindow::on_randomizeChestContentsCheckBox_clicked(bool checked)
{
    m_shouldRandomizeChestContents = checked;
}

void MainWindow::on_randomizeRequirementsCheckBox_clicked(bool checked)
{
    m_shouldRandomizeRequirements = checked;
}

void MainWindow::on_seedRNGButton_pressed()
{
    ui->rNGSeedLineEdit->setText(QString::fromStdString(std::to_string(int(m_random_device()))));
}

void MainWindow::on_exitWithoutSaving_pressed()
{
    QApplication::quit();
}

void MainWindow::on_selectInputFile_pressed()
{
    m_fName = QFileDialog::getOpenFileName(this, tr("Select an input file"), tr("/"), tr("Zelda Ocarina of Time ROM files (*.z64);; All Files (*)"));
    ui->inputFileName->setText(m_fName);
}

void MainWindow::on_inputFileName_selectionChanged()
{
    on_selectInputFile_pressed();
}
