#include "abstractcenterspicker.h"

#ifndef ABSTRACTCENTERSPICKER_CPP
#define ABSTRACTCENTERSPICKER_CPP

template<class PointType>
CentersData *AbstractCentersPicker<PointType>::getInitialCentersData()
{
    return this->initialData;
}

template<class PointType>
AbstractCentersPicker<PointType>::AbstractCentersPicker():
    initialData(nullptr)
{
}

template<class PointType>
AbstractCentersPicker<PointType>::~AbstractCentersPicker()
{
}

template<class PointType>
void AbstractCentersPicker<PointType>::divideCentersCoords(PartitionData *data)
{
    unsigned cid = 0;
    for(DensePoint* p : *(this->initialData))
    {
        double divider = (double)data->getPoints(cid).size();
        ++cid;
        if (divider == 0)
            continue;

        for(unsigned d : p->getKeys())
        {
            (*p)[d] = (*p)[d] / divider;
        }
    }
}

template<class PointType>
void AbstractCentersPicker<PointType>::addCoordsToCenter(PtrCAbstractPoint p, unsigned center)
{
    for(unsigned d : p->getKeys())
    {
        DensePoint* tmp = (*(this->initialData))[center];
        (*tmp)[d] += (*p)[d];
    }
}

#endif //ABSTRACTCENTERSPICKER_CPP
