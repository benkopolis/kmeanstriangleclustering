#ifndef HISTOGRAMCONTROLLER_H
#define HISTOGRAMCONTROLLER_H

#include <QObject>

class HistogramController : public QObject
{
    Q_OBJECT
public:
    explicit HistogramController(QObject *parent = 0);
    ~HistogramController();

signals:

    void readDone(bool ok, const QString& message);
    void countDone(bool ok, const QString& message);
    void writeDone(bool ok, const QString& message);

public slots:

    void onRead(const QString& fileName);
    void onCount();
    void onWrite(const QString& fileName);
};

#endif // HISTOGRAMCONTROLLER_H
