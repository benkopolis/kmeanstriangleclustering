#include "stemmedfileprocessingdialog.h"
#include "ui_stemmedfileprocessingdialog.h"

#include "tfidf/stemmedfileinmemoryparser.h"
#include "controllers/stemmedfileparsercontroller.h"

#include <QThread>

StemmedFileProcessingDialog::StemmedFileProcessingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StemmedFileProcessingDialog)
{
    ui->setupUi(this);
}

StemmedFileProcessingDialog::~StemmedFileProcessingDialog()
{
    delete ui;
}

void StemmedFileProcessingDialog::processFiles(const QString &inFile, const QString &outFile)
{
    ui->cbxReading->setText(ui->cbxReading->text() + " " + inFile);
    ui->cbxWriting->setText(ui->cbxWriting->text() + " " + outFile);
    this->in = inFile;
    this->out = outFile;
    this->show();

    QThread* t = new QThread(this);
    StemmedFileParserController* controller = new StemmedFileParserController(this);
    controller->moveToThread(t);
    QObject::connect(this, SIGNAL(read(QString)), controller, SLOT(onRead(QString)), Qt::QueuedConnection);
    QObject::connect(this, SIGNAL(process()), controller, SLOT(onProcess()), Qt::QueuedConnection);
    QObject::connect(this, SIGNAL(write(QString)), controller, SLOT(onWrite(QString)), Qt::QueuedConnection);
    QObject::connect(controller, SIGNAL(readDone(bool)), this, SLOT(onReadDone(bool)), Qt::QueuedConnection);
    QObject::connect(controller, SIGNAL(processDone()), this, SLOT(onProcessDone()), Qt::QueuedConnection);
    QObject::connect(controller, SIGNAL(writeDone(bool)), this, SLOT(onWriteDone(bool)), Qt::QueuedConnection);
    t->start();

    emit read(this->in);
}

void StemmedFileProcessingDialog::onReadDone(bool ok)
{
    if(ok)
    {
        this->ui->cbxReading->setChecked(true);
        emit process();
    }
    else
    {
        this->ui->cbxReading->setText("Can't process " + this->in);
        this->ui->btnClose->setEnabled(true);
    }
}

void StemmedFileProcessingDialog::onProcessDone()
{
    this->ui->cbxTfidf->setChecked(true);
    emit write(this->out);
}

void StemmedFileProcessingDialog::onWriteDone(bool ok)
{
    if(ok)
        this->ui->cbxWriting->setChecked(true);
    else
    {
        this->ui->cbxWriting->setText("Can't save to " + this->out);
        this->ui->btnClose->setEnabled(true);
        return;
    }

    this->ui->cbxDone->setChecked(true);
    this->ui->btnClose->setEnabled(true);
}

void StemmedFileProcessingDialog::on_btnClose_clicked()
{
    this->close();
}
