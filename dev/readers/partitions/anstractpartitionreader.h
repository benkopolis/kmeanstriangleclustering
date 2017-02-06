#ifndef ANSTRACTPARTITIONREADER_H
#define ANSTRACTPARTITIONREADER_H

#include "commons/partitiondata.h"

class AnstractPartitionReader
{
protected:
    AnstractPartitionReader();

public:

    AbstractPartitionReader(const AbstractPartitionReader&) = delete;
    virtual ~AbstractPartitionReader();
};

#endif // ANSTRACTPARTITIONREADER_H
