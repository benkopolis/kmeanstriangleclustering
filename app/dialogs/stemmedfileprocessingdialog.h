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
    void generateHistograms(const QString& out);

public slots:

    void processFiles(const QString &inFile, const QString &outFile);
    void onReadDone(bool ok);
    void onProcessDone();
    void onWriteDone(bool ok);
    void onGenerateHistogramsDone(bool ok, const QString &message);

private slots:
    void on_btnClose_clicked();

    void on_btnGenerateHistograms_clicked();

private:
    Ui::StemmedFileProcessingDialog *ui;

    QString in;
    QString out;
};

#endif // STEMMEDFILEPROCESSINGDIALOG_H
