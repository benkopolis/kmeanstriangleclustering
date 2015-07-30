#ifndef HISTOGRAMDIALOG_H
#define HISTOGRAMDIALOG_H

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
    void onCountDone(bool ok, const QString& message);
    void onWriteDone(bool ok, const QString& message);

signals:

    void read(const QString& fileName);
    void count();
    void write(const QString& fileName);

private slots:
    void on_btnClose_clicked();

private:
    Ui::HistogramDialog *ui;
};

#endif // HISTOGRAMDIALOG_H
