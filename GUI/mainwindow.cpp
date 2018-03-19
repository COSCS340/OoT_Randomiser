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


void MainWindow::on_outputFileName_chosen(QString arg) {
    ui->outputFileName->setText(m_ofName = arg);
    ui->selectOutputFile->setEnabled(true);
    m_dialog->deleteLater();
}

void MainWindow::on_run_complete() {
    Q_ASSERT(m_future);
    std::unique_ptr<QFutureWatcher<QString>> watcher = std::move(m_future.value());
    on_progress(watcher->future().result(), 100);
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
        connect(m_dialog, &QFileDialog::fileSelected, this, &MainWindow::on_outputFileName_chosen);
    }
}

void OoT_Randomizer::Ui::MainWindow::on_runButton_released()
{
    qWarning("clicked main button\n");
    if (true and !m_future.has_value()) {
        m_future = std::make_unique<QFutureWatcher<QString>>();
        m_future.value()->setFuture(QtConcurrent::run(&OffThreadRandomizer::ExecuteOnFile, this, std::move(m_fName), std::move(m_ofName), m_shouldRandomizeChestContents, m_shouldRandomizeColors));
        connect(m_future.value().get(), &QFutureWatcher<QString>::finished, this, &MainWindow::on_run_complete);
    }
}
