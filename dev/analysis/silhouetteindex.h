#ifndef SILHOUETTEINDEX_H
#define SILHOUETTEINDEX_H

#include "abstractindexinternal.h"
#include "distances/abstractdistance.h"

class SilhouetteIndex : public AbstractIndexInternal
{
public:
    SilhouetteIndex(AbstractDistance* dist);

    virtual double count(PartitionData* partition, AbstractPointsSpace* space);

private:

    AbstractDistance* _dist;

    double home_avg_dissimilarity(PartitionData* partition, AbstractPointsSpace* space, unsigned pointId);
    double neighbour_avg_dissimilarity(PartitionData* partition, AbstractPointsSpace* space, unsigned pointId);

    double get_avg_dist(const std::unordered_set<unsigned>& points, AbstractPointsSpace* space, unsigned pointId);
};

#endif // SILHOUETTEINDEX_H
