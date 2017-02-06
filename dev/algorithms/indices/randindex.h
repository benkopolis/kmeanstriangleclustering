#ifndef RANDINDEX_H
#define RANDINDEX_H

#include "abstractindexexternal.h"

class RandIndex : public AbstractIndexExternal
{
public:
    RandIndex();

    virtual double count(PartitionData* one, PartitionData* two);
};

#endif // RANDINDEX_H
