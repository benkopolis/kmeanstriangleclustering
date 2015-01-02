#ifndef ABSTRACTCENTERSPICKER_H
#define ABSTRACTCENTERSPICKER_H

#include "spaces/abstractpointsspace.h"
#include "commons/partitiondata.h"
#include "commons/centersdata.h"

class AbstractCentersPicker
{
public:

    virtual PartitionData *performInitialPartition(unsigned clusters, AbstractPointsSpace* ps) = 0;
    CentersData *getInitialCentersData();

protected:

    AbstractCentersPicker();

    divideCentersCoords(PartitionData* data);

    addCoordsToCenter(AbstractPoint *p, unsigned center);

private:

    CentersData * initialData;

};

#endif // ABSTRACTCENTERSPICKER_H
