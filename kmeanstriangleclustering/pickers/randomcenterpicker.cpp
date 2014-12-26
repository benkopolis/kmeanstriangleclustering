#include "randomcenterpicker.h"
#include <QtGlobal>

RandomCenterPicker::RandomCenterPicker()
{
}

PartitionData *RandomCenterPicker::performInitialPartition(unsigned clusters, AbstractPointsSpace *ps)
{
    PartitionData data = new PartitionData(clusters, ps->getNumPoints());
    unsigned cid;
    for (unsigned pid = 0; pid < ps->getNumPoints(); pid++)
    {
        cid = qrand() % clusters;
        data.assign_unsafe(pid, cid);
    }
}
