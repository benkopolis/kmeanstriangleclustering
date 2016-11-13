#ifndef CLUSTERCALCULATOR_H
#define CLUSTERCALCULATOR_H

#include "spaces/abstractpointsspace.h"
#include "abstractpoint.h"
#include "centersdata.h"
#include "partitiondata.h"
#include "commons/utils.h"

template<class Point>
class ClusterCalculator : private Utils::Where<Point, AbstractPoint>
{
public:
    ClusterCalculator() {}
    virtual ~ClusterCalculator() {}

    void recalculateCenters(CentersData* centers, PartitionData* partition, AbstractPointsSpace<Point>* space);
};

template<class Point>
void ClusterCalculator<Point>::recalculateCenters(CentersData *centers, PartitionData *partition, AbstractPointsSpace<Point>* space)
{
    unsigned center = 0;
    for (DensePoint* p : *centers)
    {
        for(unsigned dim : p->getKeys())
            (*p)[dim] = 0;

        const std::unordered_set<unsigned> &pointsInCluster = partition->getPoints(center);
        for (unsigned pid : pointsInCluster)
        {
            PtrCAbstractPoint tmp = space->getPoint(pid);
            for(unsigned dim : tmp->getKeys())
            {
                (*p)[dim] += (*tmp)[dim];
            }
        }

        ++center;
        if (pointsInCluster.size() == 0)
            continue;

        for(unsigned dim : p->getKeys())
            (*p)[dim] = (*p)[dim] / (double)pointsInCluster.size();
    }
}

#endif // CLUSTERCALCULATOR_H
