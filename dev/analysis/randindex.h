#ifndef RANDINDEXPROCESSOR_H
#define RANDINDEXPROCESSOR_H

#include "abstractindexexternal.h"

class RandIndex : public AbstractIndexExternal
{
public:
    RandIndex();

    virtual double count(const PartitionData* one, const PartitionData *two);
};

#endif // RANDINDEXPROCESSOR_H
