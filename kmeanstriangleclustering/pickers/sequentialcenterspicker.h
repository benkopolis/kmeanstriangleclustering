#ifndef SEQUENTIALCENTERSPICKER_H
#define SEQUENTIALCENTERSPICKER_H

#include "commons/abstractcenterspicker.h"

class SequentialCentersPicker : public AbstractCentersPicker
{
public:
    SequentialCentersPicker();

    virtual PartitionData *performInitialPartition(unsigned clusters, AbstractPointsSpace* ps);
};

#endif // SEQUENTIALCENTERSPICKER_H
