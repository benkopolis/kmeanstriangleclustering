#include "histogramsdrawingdata.h"

HistogramsDrawingData::HistogramsDrawingData()
{
    this->dims = new Data();
    this->coords = new Data();
}

HistogramsDrawingData::~HistogramsDrawingData()
{
    delete this->coords;
    delete this->dims;
}

QVector<QPointF> *HistogramsDrawingData::getCoords() const
{
    return coords->points;
}

void HistogramsDrawingData::addCoordsDataPoint(QPointF p)
{
    this->coords->addPoint(p);
}

QVector<QPointF> *HistogramsDrawingData::getDims() const
{
    return dims->points;
}

void HistogramsDrawingData::addDimsDataPoint(QPointF p)
{
    this->dims->addPoint(p);
}

void HistogramsDrawingData::Data::addPoint(QPointF p)
{
    this->points->push_back(p);
    if(this->max.rx() < p.rx())
        this->max.setX(p.rx());
    if(this->max.ry() < p.ry())
        this->max.setY(p.ry());
    if(this->min.rx() > p.rx())
        this->min.setX(p.rx());
    if(this->min.ry() > p.ry())
        this->min.setY(p.ry());
}
