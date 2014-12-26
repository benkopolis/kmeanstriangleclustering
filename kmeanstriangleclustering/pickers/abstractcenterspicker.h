#ifndef ABSTRACTCENTERSPICKER_H
#define ABSTRACTCENTERSPICKER_H

#include "spaces/abstractpointsspace.h"
#include "commons/partitiondata.h"

class AbstractCentersPicker
{
public:

    virtual PartitionData *performInitialPartition(unsigned clusters, AbstractPointsSpace* ps) = 0;

protected:
    AbstractCentersPicker();
};

#endif // ABSTRACTCENTERSPICKER_H
