#ifndef HISTOGRAMSDRAWINGDATA_H
#define HISTOGRAMSDRAWINGDATA_H

#include <QList>
#include <QPointF>

class HistogramsDrawingData
{
public:
    HistogramsDrawingData();
    ~HistogramsDrawingData();

    QList<QPointF> *getCoords() const;
    void setCoords(QList<QPointF> *value);

    QList<QPointF> *getDims() const;
    void setDims(QList<QPointF> *value);

private:

    QList<QPointF>* coords;
    QList<QPointF>* dims;

};

#endif // HISTOGRAMSDRAWINGDATA_H
