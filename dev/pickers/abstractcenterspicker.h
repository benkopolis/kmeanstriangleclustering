#ifndef ABSTRACTCENTERSPICKER_H
#define ABSTRACTCENTERSPICKER_H

#include "spaces/abstractpointsspace.h"
#include "commons/partitiondata.h"
#include "commons/centersdata.h"

template<typename PointType>
class AbstractCentersPicker : private Utils::Where<PointType, AbstractPoint>
{
public:

    virtual PartitionData *performInitialPartition(unsigned clusters, AbstractPointsSpace<PointType>* ps) = 0;
    CentersData *getInitialCentersData();

protected:

    AbstractCentersPicker();

    void divideCentersCoords(PartitionData* data);

    void addCoordsToCenter(PointType *p, unsigned center);

private:

    CentersData * initialData;

};

#endif // ABSTRACTCENTERSPICKER_H
