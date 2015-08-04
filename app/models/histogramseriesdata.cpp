#include "histogramseriesdata.h"

HistogramSeriesData::HistogramSeriesData() :
    points(0)
{
}

HistogramSeriesData::~HistogramSeriesData()
{
 // don't take onwership of passed pointer.
}

void HistogramSeriesData::setRectOfInterest(const QRectF &rect)
{
 // do nothing for now
}

