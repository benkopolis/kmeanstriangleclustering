#ifndef ABSTRACTCENTERSPICKER_H
#define ABSTRACTCENTERSPICKER_H

#include "spaces/abstractpointsspace.h"
#include "commons/partitiondata.h"
#include "commons/centersdata.h"

template<class PointType>
class AbstractCentersPicker : private Utils::Where<PointType, AbstractPoint>
{
public:

    virtual PartitionData *performInitialPartition(unsigned clusters, AbstractPointsSpace<PointType>* ps) = 0;
    CentersData *getInitialCentersData();

protected:

    AbstractCentersPicker();

    void divideCentersCoords(PartitionData* data);

    void addCoordsToCenter(PtrCAbstractPoint p, unsigned center);

    CentersData * initialData;

};

#include "abstractcenterspicker.cpp"

#endif // ABSTRACTCENTERSPICKER_H
