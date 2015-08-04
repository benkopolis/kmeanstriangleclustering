#ifndef HISTOGRAMSDRAWINGDATA_H
#define HISTOGRAMSDRAWINGDATA_H

#include <QVector>
#include <QPointF>
#include <cfloat>

class HistogramsDrawingData
{
public:

    HistogramsDrawingData();
    ~HistogramsDrawingData();

    QVector<QPointF> *getCoords() const;
    void addCoordsDataPoint(QPointF p);
    inline QPointF getMaxCoords() const { return this->coords->max; }
    inline QPointF getMinCoords() const { return this->coords->min; }

    QVector<QPointF> *getDims() const;
    void addDimsDataPoint(QPointF p);
    inline QPointF getMaxDims() const { return this->dims->max; }
    inline QPointF getMinDims() const { return this->dims->min; }

private:

    struct Data {
        QVector<QPointF> *points;
        QPointF max;
        QPointF min;

        Data() : max(0.0, 0.0), min(DBL_MAX, DBL_MAX) { this->points = new QVector<QPointF>(); }
        Data(const Data&) = delete;
        Data(Data&&) = delete;
        Data& operator=(const Data&) = delete;
        Data& operator=(Data&&) = delete;

        ~Data() { delete this->points; }

        void addPoint(QPointF p);
    };

    Data* coords;
    Data* dims;

};

#endif // HISTOGRAMSDRAWINGDATA_H
