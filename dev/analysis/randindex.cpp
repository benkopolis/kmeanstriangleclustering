#include "randindex.h"

#include "exceptions/differentdatasets.h"
#include "commons/logger.h"

RandIndex::RandIndex()
{

}

double RandIndex::count(const PartitionData *one, const PartitionData *two)
{
    if (one->assigned_points() != two->assigned_points()
            || one->getNumberOfClusters() != two->getNumberOfClusters())
        throw DifferentDataSets(__FILE__, __LINE__);
    double a = 0, b = 0, c = 0, d = 0;
    unsigned numPoints = one->assigned_points();
    for(unsigned x = 0; x < numPoints; ++x)
    {
        for(unsigned y = x + 1; y < numPoints; ++y)
        {
            if (one->getCluster(x) == one->getCluster(y)
                    && two->getCluster(x) == two->getCluster(y))
                a += 1;
            else if (one->getCluster(x) != one->getCluster(y)
                     && two->getCluster(x) != two->getCluster(y))
                b += 1;
            else if (one->getCluster(x) == one->getCluster(y)
                     && two->getCluster(x) != two->getCluster(y))
                c += 1;
            else if (one->getCluster(x) != one->getCluster(y)
                     && two->getCluster(x) == two->getCluster(y))
                d += 1;
        }
    }

    double rand = (a + b) / (a + b + c + d);
    char str[35];
    std::sprintf(str, "Rand index is %.6f", rand);
    logger::log(str);
    return rand;
}

