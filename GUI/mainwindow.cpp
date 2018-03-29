#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "offthreadrandomizer.h"
#include <Common/game.hpp>

#include <QFileDialog>
#include <QtConcurrent>
#include <QFutureWatcher>
#include <random>
#include <memory>
#include <iostream>
namespace OoT_Randomizer {

namespace Ui {
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new ::Ui::MainWindow), m_prng(), m_shouldRandomizeColors(false),
    m_shouldRandomizeChestContents(false), m_shouldRandomizeRequirements(false),
    m_random_device(), m_dialog(nullptr), m_future()
{
    this->ui->setupUi(this);
    this->ui->rNGSeedLineEdit->setValidator(new QIntValidator);
    ui->inputFileName->setReadOnly(true);
    this->setWindowTitle(tr("Ocarina of Time Randomizer"));
}

MainWindow::~MainWindow()
{
    if (m_future) {
        m_future->future().result();
    }
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
    qWarning("destroyed dialog");
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

void MainWindow::on_progress(QString str, int value) {
    Q_ASSERT(m_future);
    ui->statusLabel->setText(str);
    ui->progressBar->setValue(value);
}


void MainWindow::onOutputfilenameChosen(QString arg) {
    ui->outputFileName->setText(m_ofName = arg);
    ui->selectOutputFile->setEnabled(true);
    m_dialog->deleteLater();
}

void MainWindow::onRunComplete() {
    Q_ASSERT(m_future);
    on_progress(m_future->future().result(), 100);
    m_future.reset();
}

}

}

void OoT_Randomizer::Ui::MainWindow::on_selectOutputFile_clicked(bool checked)
{
    if (!checked) {
        m_dialog = new QFileDialog(this, tr("Select an output file"), tr("/home"), tr("Zelda Ocarina of Time ROM files (*.z64);; All Files (*)"));
        m_dialog->setFileMode(QFileDialog::FileMode::AnyFile);
        m_dialog->setAcceptMode(QFileDialog::AcceptMode::AcceptSave);
        m_dialog->show();
        connect(m_dialog, &QFileDialog::fileSelected, this, &MainWindow::onOutputfilenameChosen);
    }
}

void OoT_Randomizer::Ui::MainWindow::on_runButton_released()
{
    if (!m_future) {
        m_future.reset(new QFutureWatcher<QString>());
        auto randomizer = std::make_shared<OffThreadRandomizer>();
        connect(randomizer.get(), &OffThreadRandomizer::ReportProgress, this, &MainWindow::on_progress, Qt::QueuedConnection);
        m_future->setFuture(QtConcurrent::run(&OffThreadRandomizer::ExecuteOnFile, randomizer, std::move(m_fName), std::move(m_ofName), m_shouldRandomizeChestContents, m_shouldRandomizeColors));
        connect(m_future.get(), &QFutureWatcher<QString>::finished, this, &MainWindow::onRunComplete);
    }
}
