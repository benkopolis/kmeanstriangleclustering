#include "sequentialcenterspicker.h"

template<class PointType>
SequentialCentersPicker<PointType>::SequentialCentersPicker()
{
}

template<class PointType>
PartitionData *SequentialCentersPicker<PointType>::performInitialPartition(unsigned clusters, AbstractPointsSpace<PointType> *ps)
{
    PartitionData *data = new PartitionData(clusters, ps->getNumPoints());
    unsigned cid;
    for (unsigned pid = 0; pid < ps->getNumPoints(); pid++)
    {
        cid = pid % clusters;
        data->assign_unsafe(pid, cid);
        this->addCoordsToCenter(ps->getPoint(pid), cid);
    }

    this->divideCentersCoords(data);
    return data;
}
