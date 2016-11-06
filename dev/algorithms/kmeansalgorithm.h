#ifndef KMEANSALGORITHM_H
#define KMEANSALGORITHM_H

#include <unordered_map>
#include <utility>

#include "abstractalgorithm.h"

template<class Point, class Distance, class Picker, class Space>
class KMeansAlgorithm : public AbstractAlgorithm<Point, Distance, Picker, Space>
{
public:
    KMeansAlgorithm(Distance *distance,
                    Picker<Point> *picker,
                    Space<Point> *space,
                    unsigned clusters,
                    unsigned iterations);

    virtual void execute();

protected:

    unsigned _numClusters;
    unsigned _iterations;
    // cluster id; point id = distance
    std::unordered_map<std::pair<unsigned, unsigned>, double> _distanceValues;
};

template<class Point, class Distance, class Picker, class Space>
KMeansAlgorithm<Point, Distance, Picker, Space>::KMeansAlgorithm(Distance *distance,
        Picker<Point> *picker,
        Space<Point> *space,
        unsigned clusters,
        unsigned iterations) :
    AbstractAlgorithm(distance, picker, space),
    _numClusters(clusters),
    _iterations(iterations)
{
}

template<class Point, class Distance, class Picker, class Space>
void KMeansAlgorithm<Point, Distance, Picker, Space>::execute()
{
    this->_partition - this->_picker->performInitialPartition(
                this->_numClusters, this->_space);
    this->_centers = this->_picker->getInitialCentersData();
    bool moved = true;
    unsigned looped = 0, centerId = 0, numPoints = this->_space->getNumOfInsertedPoints();
    unsigned assignedClusterId = 0;
    double dist = 0, currentAssignedDist;
    do
    {
        for(DensePoint* center : this->_centers)
        {
            for(unsigned i = 0; i < numPoints; ++i)
            {
                dist = this->_distance->distance(center, point);
                if (this->_distanceValues.count({centerId, i}) > 0)
                    this->_distanceValues[std::make_pair(centerId, i)] = dist;
                else
                    this->_distanceValues.insert({{centerId, i}, dist});
                // this moght be a better cluster, let's check it
                assignedClusterId = this->_partition->getCluster(i);
                if (assignedClusterId = centerId)
                    continue; // if already assigned, there is no need to check
                currentAssignedDist = this->_distanceValues[std::make_pair(assignedClusterId, i)];
                if(dist < currentAssignedDist) // check if can be assigned to the curently used center
                    this->_partition->assign(i, centerId); // if so, assign it
            }
            ++centerId;
        }
    } while(moved && looped < this->_iterations);
}


#endif // KMEANSALGORITHM_H
