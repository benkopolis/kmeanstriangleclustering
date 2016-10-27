#include "randomcenterpicker.h"
#include <QtGlobal>

template<class PointType>
RandomCenterPicker<PointType>::RandomCenterPicker()
{
}

template<class PointType>
PartitionData *RandomCenterPicker<PointType>::performInitialPartition(unsigned clusters, AbstractPointsSpace<PointType> *ps)
{
    PartitionData* data = new PartitionData(clusters, ps->getDeclaredNumPoints());
    this->initialData = new CentersData(clusters, ps->getNumDimensions());
    unsigned cid;
    for (unsigned pid = 0; pid < ps->getDeclaredNumPoints(); pid++)
    {
        cid = qrand() % clusters;
        data->assign_unsafe(pid, cid);
        this->addCoordsToCenter(ps->getPoint(pid), cid);
    }

    this->divideCentersCoords(data);

    return data;
}
