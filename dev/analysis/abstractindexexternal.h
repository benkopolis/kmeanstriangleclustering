#ifndef ABSTRACTINDEX_H
#define ABSTRACTINDEX_H

#include "commons/partitiondata.h"

class AbstractIndexExternal
{
protected:
    AbstractIndexExternal();

public:
    AbstractIndexExternal(const AbstractIndexExternal&) = delete;
    AbstractIndexExternal(AbstractIndexExternal&&);
    virtual ~AbstractIndexExternal();

    virtual double count(const PartitionData* one, const PartitionData* two) = 0;
};


#endif // ABSTRACTINDEX_H
