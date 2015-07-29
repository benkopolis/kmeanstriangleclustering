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
    explicit StemmedFileProcessingDialog(QWidget *parent = 0);
    ~StemmedFileProcessingDialog();

signals:

    void read(const QString& in);
    void process();
    void write(const QString& out);

public slots:

    void processFiles(const QString &inFile, const QString &outFile);
    void onReadDone(bool ok);
    void onProcessDone();
    void onWriteDone(bool ok);

private slots:
    void on_btnClose_clicked();

private:
    Ui::StemmedFileProcessingDialog *ui;

    QString in;
    QString out;
};

#endif // STEMMEDFILEPROCESSINGDIALOG_H
