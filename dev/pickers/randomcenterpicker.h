#ifndef RANDOMCENTERPICKER_H
#define RANDOMCENTERPICKER_H

#include "abstractcenterspicker.h"

class RandomCenterPicker : public AbstractCentersPicker
{
public:
    RandomCenterPicker();

    virtual PartitionData *performInitialPartition(unsigned clusters, AbstractPointsSpace* ps);
};

#endif // RANDOMCENTERPICKER_H
