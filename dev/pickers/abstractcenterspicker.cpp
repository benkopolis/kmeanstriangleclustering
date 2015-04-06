#include "abstractcenterspicker.h"

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
    for(unsigned cid : this->initialData)
    {
        DensePoint* p = this->initialData[cid];
        for(unsigned d : p->getKeys())
        {
            (*p)[d] = (*p)[d] / data->getPoints(cid).size();
        }
    }
}

template<typename PointType>
void AbstractCentersPicker<PointType>::addCoordsToCenter(PointType *p, unsigned center)
{
    AbstractPoint* q = dynamic_cast<AbstractPoint*>(p);
    for(unsigned d : q->getKeys())
    {
        this->initialData[center][d] += (*q)[d];
    }
}
