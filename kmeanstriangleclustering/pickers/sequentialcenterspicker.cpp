#include "sequentialcenterspicker.h"

SequentialCentersPicker::SequentialCentersPicker()
{
}

PartitionData *SequentialCentersPicker::performInitialPartition(unsigned clusters, AbstractPointsSpace *ps)
{
    PartitionData data = new PartitionData(clusters, ps->getNumPoints());
    unsigned cid;
    for (unsigned pid = 0; pid < ps->getNumPoints(); pid++)
    {
        cid = pid % clusters;
        data.assign_unsafe(pid, cid);
    }
}
