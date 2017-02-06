#ifndef NORMALPARTITIONREADER_H
#define NORMALPARTITIONREADER_H

#include "abstractpartitionreader.h"

class NormalPartitionReader : public AbstractPartitionReader
{
public:
    NormalPartitionReader();
    virtual ~NormalPartitionReader();

    virtual PartitionData* readFromFile(const char* fileName);
};

#endif // NORMALPARTITIONREADER_H
