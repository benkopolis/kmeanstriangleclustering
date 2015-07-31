#include "histogramcontroller.h"

HistogramController::HistogramController(QObject *parent)
    : QObject(parent),
      histograms(0),
      data(0),
      dataReady(false)
{
}

HistogramController::~HistogramController()
{
    delete this->histograms;
    this->histograms = 0;
}

void HistogramController::onRead(const QString &fileName)
{
    this->histograms = new TfidfHistogramGenerator();
    QByteArray ba = fileName.toLatin1();
    try {
        this->histograms->generateHistograms(ba.data());
    } catch(IOException e) {
        emit readDone(false, e.what());
        return;
    }

    emit readDone(true, "");
}

void HistogramController::onReadHistograms(const QString &coords, const QString &dims)
{
    this->histograms = new TfidfHistogramGenerator();
    QByteArray ba1 = coords.toLatin1(), ba2 = dims.toLatin1();
    try {
        this->histograms->loadCoordsHistogram(ba1.data());
        this->histograms->loadDimsHistogram(ba2.data());
    } catch(IOException e) {
        emit readHistogramsDone(false, e.what());
        return;
    }

    emit readHistogramsDone(true, "");

    this->fillDrawingData();
}

void HistogramController::onWrite(const QString &fileName)
{
    QByteArray ba = fileName.toLatin1();
    try {
        this->histograms->save(ba.data());
    } catch(IOException e) {
        emit writeDone(false, e.what());
        return;
    }

    emit writeDone(true, "");

    this->fillDrawingData();
}

void HistogramController::onGetHistogramsData()
{
    if(this->dataReady)
        emit histogramsData(this->data);
    else
        emit histogramsData(0);
}

void HistogramController::fillDrawingData()
{
    this->data = new HistogramsDrawingData();
    for(auto pair : this->histograms->getCoordsValuesFrequency()) {
        this->data->getCoords()->append(QPointF((qreal)pair.first, (qreal)pair.second));
    }
    for(auto pair: this->histograms->getNonZeroCoordsFrequency()) {
        this->data->getDims()->append(QPointF((qreal)pair.first, (qreal)pair.second));
    }

    this->dataReady = true;
}

