#include "silhouetteindex.h"

#include <limits>

SilhouetteIndex::SilhouetteIndex(AbstractDistance *dist)
{
    this->_dist = dist;
}

double SilhouetteIndex::count(PartitionData *partition, AbstractPointsSpace *space)
{
    double total = 0;
    for(unsigned i = 0; i < space->getNumOfInsertedPoints(); ++i)
    {
        double a = this->home_avg_dissimilarity(partition, space, i);
        double b = this->neighbour_avg_dissimilarity(partition, space, i);
        if (a < b)
            total = total + ((b - a) / b);
        else
            total = total + ((b - a) / a);
    }

    return total / double(space->getNumOfInsertedPoints());
}

double SilhouetteIndex::home_avg_dissimilarity(PartitionData *partition, AbstractPointsSpace *space, unsigned pointId)
{
    unsigned homeCluster = partition->getCluster(pointId);
    return this->get_avg_dist(partition->getPoints(homeCluster), space, pointId);
}

double SilhouetteIndex::neighbour_avg_dissimilarity(PartitionData *partition, AbstractPointsSpace *space, unsigned pointId)
{
    unsigned homeCluster = partition->getCluster(pointId);
    double total = std::numeric_limits<double>::max(), tmp = 0;
    for(unsigned cluster = 0; cluster < partition->getNumberOfClusters(); ++cluster)
    {
        if(cluster == homeCluster)
            continue;
        tmp = this->get_avg_dist(partition->getPoints(cluster), space, pointId);
        if (tmp < total)
            total = tmp;
    }

    return total;
}

double SilhouetteIndex::get_avg_dist(const std::unordered_set<unsigned> &points, AbstractPointsSpace *space, unsigned pointId)
{
    double total = 0, iters = 0;
    for(unsigned point : points)
    {
        if (point == pointId)
            continue;
        total = total + this->_dist->distance(space->getPoint(pointId), space->getPoint(point));
        ++iters;
    }

    return total = total / iters;
}

