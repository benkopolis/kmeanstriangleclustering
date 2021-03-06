#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialogs/stemmedfileprocessingdialog.h"
#include "dialogs/histogramdialog.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnClose_clicked()
{
    this->close();
}

void MainWindow::on_btnCountTFIDF_clicked()
{
    QString fileToProcess = QFileDialog::getOpenFileName(
                this,
                "Please choose file with stemmed documents",
                "/home/zby/MAGISTERKA/kmeanstriangleclustering/data");
    QString fileToStore = QFileDialog::getSaveFileName(
                this,
                "Please choose or create a file to save results of TFIDF processing",
                "/home/zby/MAGISTERKA/kmeanstriangleclustering/data");
    StemmedFileProcessingDialog *dialog = new StemmedFileProcessingDialog(this);
    dialog->processFiles(fileToProcess, fileToStore);
}

void MainWindow::on_btnGetStatsForTFIDF_clicked()
{
    QString fileToProcess = QFileDialog::getOpenFileName(
                this,
                "Please choose TF-IDF file",
                "/home/zby/MAGISTERKA/kmeanstriangleclustering/data");
    HistogramDialog* dialog = new HistogramDialog(this);
    dialog->processTfidf(fileToProcess);
}

void MainWindow::on_btnLoadHist_clicked()
{
    HistogramDialog* dialog = new HistogramDialog(this);
    dialog->readHistogramsData();
}
