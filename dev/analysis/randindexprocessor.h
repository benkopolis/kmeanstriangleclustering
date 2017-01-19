#ifndef RANDINDEXPROCESSOR_H
#define RANDINDEXPROCESSOR_H

#include "commons/partitiondata.h"

class RandIndexProcessor
{
public:
    RandIndexProcessor();

    double process(const PartitionData* one, const PartitionData* two);
};

#endif // RANDINDEXPROCESSOR_H
