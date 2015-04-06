#include "abstractcenterspicker.h"

template<typename PointType>
CentersData *AbstractCentersPicker::getInitialCentersData()
{
    return this->initialData;
}

template<typename PointType>
AbstractCentersPicker::AbstractCentersPicker():
    initialData(0)
{
}

template<typename PointType>
void AbstractCentersPicker::divideCentersCoords(PartitionData *data)
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
void AbstractCentersPicker::addCoordsToCenter(PointType *p, unsigned center)
{
    AbstractPoint* p = ps->getPoint(pid);
    for(unsigned d : p->getKeys())
    {
        this->initialData[cid][d] += (*p)[d];
    }
}
