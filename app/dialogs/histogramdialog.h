#ifndef HISTOGRAMDIALOG_H
#define HISTOGRAMDIALOG_H

#include "models/histogramsdrawingdata.h"

#include <QDialog>

namespace Ui {
class HistogramDialog;
}

class HistogramDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HistogramDialog(QWidget *parent = 0);
    ~HistogramDialog();

public slots:
    void processTfidf(const QString& fileName);
    void onReadDone(bool ok, const QString& message);
    void onWriteDone(bool ok, const QString& message);
    void onReadHistogramsData(bool ok, const QString& message);
    void readHistogramsData();
    void onHistogramsData(HistogramsDrawingData* histograms);

signals:

    void read(const QString& fileName);
    void readHistograms(const QString& coords, const QString& dims);
    void requestHistogramsData();
    void write(const QString& fileName);

private slots:
    void on_btnClose_clicked();

    void on_btnView_clicked();

private:
    Ui::HistogramDialog *ui;
    HistogramsDrawingData* histograms;
    QString fileName;
};

#endif // HISTOGRAMDIALOG_H
