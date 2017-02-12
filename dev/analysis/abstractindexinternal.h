#ifndef ABSTRACTINDEXINTERNAL_H
#define ABSTRACTINDEXINTERNAL_H

#include "commons/partitiondata.h"
#include "spaces/abstractpointsspace.h"

class AbstractIndexInternal
{
protected:
    AbstractIndexInternal();

public:
    AbstractIndexInternal(const AbstractIndexInternal&) = delete;
    AbstractIndexInternal(AbstractIndexInternal&&) = delete;
    virtual ~AbstractIndexInternal();

    virtual double count(const PartitionData* partition, const AbstractPointsSpace* space) = 0;
};
#endif // ABSTRACTINDEXINTERNAL_H
