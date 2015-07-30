#include "histogramdialog.h"
#include "ui_histogramdialog.h"

#include "controllers/histogramcontroller.h"

#include <QThread>

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
    QThread *t = new QThread(this);
    HistogramController *controler = new HistogramController(this);
    controler->moveToThread(t);
    t->start();

    QObject::connect(this, SIGNAL(read(QString)), controler, SLOT(onRead(QString)), Qt::QueuedConnection);
    QObject::connect(this, SIGNAL(count()), controler, SLOT(onCount()), Qt::QueuedConnection);
    QObject::connect(this, SIGNAL(write(QString)), controler, SLOT(onWrite(QString)), Qt::QueuedConnection);
    QObject::connect(controler, SIGNAL(readDone(bool,QString)), this, SLOT(onReadDone(bool,QString)));
    QObject::connect(controler, SIGNAL(countDone(bool,QString)), this, SLOT(onCountDone(bool,QString)));
    QObject::connect(controler, SIGNAL(writeDone(bool,QString)), this, SLOT(onWriteDone(bool,QString)));

    emit read(fileName);
    this->show();
}

void HistogramDialog::onReadDone(bool ok, const QString &message)
{

}

void HistogramDialog::onCountDone(bool ok, const QString &message)
{

}

void HistogramDialog::onWriteDone(bool ok, const QString &message)
{

}

void HistogramDialog::on_btnClose_clicked()
{
    this->close();
}
