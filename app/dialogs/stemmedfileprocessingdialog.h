#ifndef STEMMEDFILEPROCESSINGDIALOG_H
#define STEMMEDFILEPROCESSINGDIALOG_H

#include <QDialog>

namespace Ui {
class StemmedFileProcessingDialog;
}

class StemmedFileProcessingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StemmedFileProcessingDialog(const QString &inFile, const QString &outFile, QWidget *parent = 0);
    ~StemmedFileProcessingDialog();

public slots:

    void processFiles();

private slots:
    void on_btnClose_clicked();

private:
    Ui::StemmedFileProcessingDialog *ui;

    QString stemmedDocsFile;
    QString tfIdfResultFile;
};

#endif // STEMMEDFILEPROCESSINGDIALOG_H
