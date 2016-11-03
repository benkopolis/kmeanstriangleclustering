#include "abstractcenterspicker.h"

#ifndef ABSTRACTCENTERSPICKER_CPP
#define ABSTRACTCENTERSPICKER_CPP

template<typename PointType>
CentersData *AbstractCentersPicker<PointType>::getInitialCentersData()
{
    return this->initialData;
}

template<typename PointType>
AbstractCentersPicker<PointType>::AbstractCentersPicker():
    initialData(0)
{
}

template<typename PointType>
void AbstractCentersPicker<PointType>::divideCentersCoords(PartitionData *data)
{
    unsigned cid = 0;
    for(DensePoint* p : *(this->initialData))
    {
        for(unsigned d : p->getKeys())
        {
            (*p)[d] = (*p)[d] / data->getPoints(cid).size();
        }

        ++cid;
    }
}

template<typename PointType>
void AbstractCentersPicker<PointType>::addCoordsToCenter(PtrCAbstractPoint p, unsigned center)
{
    for(unsigned d : p->getKeys())
    {
        DensePoint* tmp = (*(this->initialData))[center];
        (*tmp)[d] += (*p)[d];
    }
}

#endif //ABSTRACTCENTERSPICKER_CPP
