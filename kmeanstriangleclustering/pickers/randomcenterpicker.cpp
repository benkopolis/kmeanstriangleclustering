#include "randomcenterpicker.h"
#include <QtGlobal>

RandomCenterPicker::RandomCenterPicker()
{
}

PartitionData *RandomCenterPicker::performInitialPartition(unsigned clusters, AbstractPointsSpace *ps)
{
    PartitionData* data = new PartitionData(clusters, ps->getNumPoints());
    this->initialData = new CentersData(clusters, ps->getNumDimensions());
    unsigned cid;
    for (unsigned pid = 0; pid < ps->getNumPoints(); pid++)
    {
        cid = qrand() % clusters;
        data->assign_unsafe(pid, cid);
        this->addCoordsToCenter(ps->getPoint(pid), cid);
    }

    this->divideCentersCoords(data);

    return data;
}
