#ifndef TRANSPOSEDPARTITIONREADER_H
#define TRANSPOSEDPARTITIONREADER_H

#include "abstractpartitionreader.h"

class TransposedPartitionReader : public AbstractPartitionReader
{
public:
    TransposedPartitionReader();
    virtual ~TransposedPartitionReader();

    virtual PartitionData* readFromFile(const char* fileName);
};

#endif // TRANSPOSEDPARTITIONREADER_H
