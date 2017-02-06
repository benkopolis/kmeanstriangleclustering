#ifndef ABSTRACTINDEXINTERNAL_H
#define ABSTRACTINDEXINTERNAL_H

#include "commons/partitiondata.h"
#include "spaces/abstractpointsspace.h"

class AbstractIntexInternal
{
protected:
    AbstractIntexInternal();

public:
    AbstractIntexInternal(const AbstractIntexInternal&) = delete;
    AbstractIntexInternal(AbstractIntexInternal&&) = delete;
    virtual ~AbstractIntexInternal();

    virtual double count(const PartitionData* partition, const AbstractPointsSpace* space) = 0;
};
#endif // ABSTRACTINDEXINTERNAL_H
