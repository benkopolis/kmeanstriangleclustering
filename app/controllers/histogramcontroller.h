#ifndef HISTOGRAMCONTROLLER_H
#define HISTOGRAMCONTROLLER_H

#include "tfidf/tfidfhistogramgenerator.h"
#include "models/histogramsdrawingdata.h"

#include <QObject>

class HistogramController : public QObject
{
    Q_OBJECT
public:
    explicit HistogramController(QObject *parent = 0);
    ~HistogramController();

signals:

    void readDone(bool ok, const QString& message);
    void writeDone(bool ok, const QString& message);
    void readHistogramsDone(bool ok, const QString& mesage);
    void histogramsData(HistogramsDrawingData* histograms);

public slots:

    void onRead(const QString& fileName);
    void onReadHistograms(const QString& coords, const QString& dims);
    void onWrite(const QString& fileName);
    void onGetHistogramsData();

private:

    void fillDrawingData();

    TfidfHistogramGenerator* histograms;
    HistogramsDrawingData* data;
    bool dataReady;
};

#endif // HISTOGRAMCONTROLLER_H
