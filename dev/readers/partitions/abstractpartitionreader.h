#ifndef ABSTRACTPARTITIONREADER_H
#define ABSTRACTPARTITIONREADER_H

#include "commons/partitiondata.h"

class AbstractPartitionReader
{
protected:
    AbstractPartitionReader();

public:

    AbstractPartitionReader(const AbstractPartitionReader&) = delete;
    AbstractPartitionReader(AbstractPartitionReader&&) = delete;
    virtual ~AbstractPartitionReader();

    virtual PartitionData* readFromFile(const char* fileName) = 0;
};

#endif // ABSTRACTPARTITIONREADER_H
