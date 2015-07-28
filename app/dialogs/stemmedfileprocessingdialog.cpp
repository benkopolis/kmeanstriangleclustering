#include "stemmedfileprocessingdialog.h"
#include "ui_stemmedfileprocessingdialog.h"

#include "tfidf/stemmedfileinmemoryparser.h"

StemmedFileProcessingDialog::StemmedFileProcessingDialog(const QString& inFile, const QString& outFile, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StemmedFileProcessingDialog),
    stemmedDocsFile(inFile),
    tfIdfResultFile(outFile)
{
    ui->setupUi(this);
    ui->cbxReading->setText(ui->cbxReading->text() + " " + inFile);
    ui->cbxWriting->setText(ui->cbxWriting->text() + " " + outFile);
}

StemmedFileProcessingDialog::~StemmedFileProcessingDialog()
{
    delete ui;
}

void StemmedFileProcessingDialog::processFiles()
{
    StemmedFileInMemoryParser parser;
    bool step = parser.fillWithData(this->stemmedDocsFile);
    if(step)
        this->ui->cbxReading->setChecked(true);
    else
    {
        this->ui->cbxReading->setText("Can't process " + this->stemmedDocsFile);
        this->ui->btnClose->setEnabled(true);
        return;
    }

    parser.countTfidf();
    this->ui->cbxTfidf->setChecked(true);
    step = parser.storeTfidfInFile(this->tfIdfResultFile);
    if(step)
        this->ui->cbxWriting->setChecked(true);
    else
    {
        this->ui->cbxWriting->setText("Can't sae to " + this->tfIdfResultFile);
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
