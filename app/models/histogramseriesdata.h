#ifndef HISTOGRAMSERIESDATA_H
#define HISTOGRAMSERIESDATA_H

#include <qwt_series_data.h>
#include <QPointF>
#include <QRectF>
#include <QVector>

class HistogramSeriesData : public QwtSeriesData<QPointF>
{
public:
    HistogramSeriesData();
    virtual ~HistogramSeriesData();

    virtual inline size_t size() const { return this->points == 0 ? 0 : this->points->size(); }

    /*
     * @brief Don't want to throw in this method, without throw(sth) declaration, and
     * can't change the header since it's inherited.
     */
    virtual inline QPointF sample(size_t i) const { return this->points == 0 ? QPointF(-1, -1) : (*(this->points))[i]; }
    virtual inline QRectF boundingRect() const { return this->d_boundingRect; }
    virtual void setRectOfInterest(const QRectF& rect);

    inline void setSamples(QVector<QPointF>* pArray) { this->points = pArray; }
    inline void setBoundingRect(QPointF max) const { this->d_boundingRect = QRectF(0, 0, max.rx() + 20, max.ry() + 20); }

protected:

    QVector<QPointF>* points;
};

#endif // HISTOGRAMSERIESDATA_H
