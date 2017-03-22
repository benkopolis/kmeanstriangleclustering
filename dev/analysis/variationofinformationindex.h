#ifndef VARIATIONOFINFORMATIONINDEX_H
#define VARIATIONOFINFORMATIONINDEX_H

#include "abstractindexexternal.h"

class VariationOfInformationIndex : AbstractIndexExternal
{
public:
    VariationOfInformationIndex();
    virtual ~VariationOfInformationIndex();

    virtual double count(const PartitionData *one, const PartitionData *two);
};

#endif // VARIATIONOFINFORMATIONINDEX_H
