#ifndef RANDOMCENTERPICKER_H
#define RANDOMCENTERPICKER_H

#include "abstractcenterspicker.h"

template<typename PointType>
class RandomCenterPicker : public AbstractCentersPicker<PointType>
{
public:
    RandomCenterPicker();

    virtual PartitionData *performInitialPartition(unsigned clusters, AbstractPointsSpace<PointType>* ps);
};

#endif // RANDOMCENTERPICKER_H
