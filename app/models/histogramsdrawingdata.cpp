#include "histogramsdrawingdata.h"

HistogramsDrawingData::HistogramsDrawingData()
{
    this->dims = new QList<QPointF>();
    this->coords = new QList<QPointF>();
}

HistogramsDrawingData::~HistogramsDrawingData()
{
    delete this->coords;
    delete this->dims;
}

QList<QPointF> *HistogramsDrawingData::getCoords() const
{
    return coords;
}

void HistogramsDrawingData::setCoords(QList<QPointF> *value)
{
    coords = value;
}

QList<QPointF> *HistogramsDrawingData::getDims() const
{
    return dims;
}

void HistogramsDrawingData::setDims(QList<QPointF> *value)
{
    dims = value;
}



