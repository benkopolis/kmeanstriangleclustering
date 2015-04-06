#ifndef SEQUENTIALCENTERSPICKER_H
#define SEQUENTIALCENTERSPICKER_H

#include "abstractcenterspicker.h"

template<class PointType>
class SequentialCentersPicker : public AbstractCentersPicker<PointType>
{
public:
    SequentialCentersPicker();

    virtual PartitionData *performInitialPartition(unsigned clusters, AbstractPointsSpace<PointType>* ps);
};

#endif // SEQUENTIALCENTERSPICKER_H
