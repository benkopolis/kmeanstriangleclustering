#ifndef SILHOUETTEINDEX_H
#define SILHOUETTEINDEX_H

#include "abstractindexinternal.h"

class SilhouetteIndex : public AbstractIndexInternal
{
public:
    SilhouetteIndex();

    virtual double count(PartitionData* partition, AbstractPointsSpace* space);
};

#endif // SILHOUETTEINDEX_H
