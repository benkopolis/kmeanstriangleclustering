#include "abstractcenterspicker.h"

CentersData *AbstractCentersPicker::getInitialCentersData()
{
    return this->initialData;
}

AbstractCentersPicker::AbstractCentersPicker():
    initialData(0)
{
}

AbstractCentersPicker::divideCentersCoords(PartitionData *data)
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

AbstractCentersPicker::addCoordsToCenter(AbstractPoint* p, unsigned center)
{
    AbstractPoint* p = ps->getPoint(pid);
    for(unsigned d : p->getKeys())
    {
        this->initialData[cid][d] += (*p)[d];
    }
}
