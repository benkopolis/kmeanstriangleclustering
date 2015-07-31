#include "histogramdialog.h"
#include "ui_histogramdialog.h"

#include "controllers/histogramcontroller.h"
#include "views/histogramsview.h"

#include <QThread>
#include <QFileDialog>

HistogramDialog::HistogramDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HistogramDialog)
{
    ui->setupUi(this);
}

HistogramDialog::~HistogramDialog()
{
    delete ui;
}

void HistogramDialog::processTfidf(const QString &fileName)
{
    this->fileName = fileName;
    QThread *t = new QThread(this);
    HistogramController *controler = new HistogramController(this);
    controler->moveToThread(t);
    t->start();

    QObject::connect(this, SIGNAL(read(QString)), controler, SLOT(onRead(QString)), Qt::QueuedConnection);
    QObject::connect(this, SIGNAL(write(QString)), controler, SLOT(onWrite(QString)), Qt::QueuedConnection);
    QObject::connect(controler, SIGNAL(readDone(bool,QString)), this, SLOT(onReadDone(bool,QString)), Qt::QueuedConnection);
    QObject::connect(controler, SIGNAL(writeDone(bool,QString)), this, SLOT(onWriteDone(bool,QString)), Qt::QueuedConnection);
    QObject::connect(this, SIGNAL(requestHistogramsData()), controler, SLOT(onGetHistogramsData()), Qt::QueuedConnection);
    QObject::connect(controler, SIGNAL(histogramsData(HistogramsDrawingData*)), this, SLOT(onHistogramsData(HistogramsDrawingData*)), Qt::QueuedConnection);

    emit read(this->fileName);
    this->show();
}

void HistogramDialog::onReadDone(bool ok, const QString &message)
{
    if(ok) {
        this->ui->cbxRead->setChecked(true);
        emit write(this->fileName);
    } else {
        this->ui->cbxRead->setText(message);
        this->ui->btnClose->setEnabled(true);
    }
}

void HistogramDialog::onWriteDone(bool ok, const QString &message)
{
    if(ok)
        this->ui->cbxWrite->setChecked(true);
    else
        this->ui->cbxWrite->setText(message);
    this->ui->btnView->setEnabled(true);
    this->ui->btnClose->setEnabled(true);
}

void HistogramDialog::onReadHistogramsData(bool ok, const QString &message)
{
    if(ok) {
        this->ui->cbxRead->setChecked(true);
        this->ui->cbxRead->setText("Read both histogram files");
        this->ui->cbxWrite->setVisible(false);
        this->ui->btnView->setEnabled(true);
    } else {
        this->ui->cbxRead->setText(message);
    }

    this->ui->btnClose->setEnabled(true);
}

void HistogramDialog::readHistogramsData()
{
    QString f1 = QFileDialog::getOpenFileName(this,
                                              "Choose first histogram file from a pair",
                                              "/home/zby/MAGISTERKA/kmeanstriangleclustering/data",
                                              "Coords values histograms (*.chist)");
    QString f2 = QFileDialog::getOpenFileName(this,
                                              "Choose first histogram file from a pair",
                                              "/home/zby/MAGISTERKA/kmeanstriangleclustering/data",
                                              "Nonzero dimensions count histograms (*.dhist)");
    QThread *t = new QThread(this);
    HistogramController *controler = new HistogramController(this);
    controler->moveToThread(t);
    t->start();

    QObject::connect(this, SIGNAL(readHistograms(QString,QString)), controler, SLOT(onReadHistograms(QString,QString)), Qt::QueuedConnection);
    QObject::connect(this, SIGNAL(requestHistogramsData()), controler, SLOT(onGetHistogramsData()));
    QObject::connect(controler, SIGNAL(readHistogramsDone(bool,QString)), this, SLOT(onReadHistogramsData(bool,QString)), Qt::QueuedConnection);
    QObject::connect(controler, SIGNAL(histogramsData(HistogramsDrawingData*)), this, SLOT(onHistogramsData(HistogramsDrawingData*)), Qt::QueuedConnection);

    emit readHistograms(f1, f2);
}

void HistogramDialog::onHistogramsData(HistogramsDrawingData *histograms)
{
    this->histograms = histograms;
}

void HistogramDialog::on_btnClose_clicked()
{
    this->close();
}

void HistogramDialog::on_btnView_clicked()
{
    emit readHistogramsData();
}
