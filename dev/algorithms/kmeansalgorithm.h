#ifndef KMEANSALGORITHM_H
#define KMEANSALGORITHM_H

#include <unordered_map>
#include <utility>

#include "abstractalgorithm.h"
#include "commons/clustercalculator.h"

template<class Point>
class KMeansAlgorithm : public AbstractAlgorithm<Point>
{
public:
    KMeansAlgorithm(AbstractDistance *distance,
                    AbstractCentersPicker<Point> *picker,
                    AbstractPointsSpace<Point> *space,
                    unsigned clusters,
                    unsigned iterations);

    virtual void execute();

    inline unsigned getNumberOfIterations() const { return this->_looped; }

protected:

    unsigned _numClusters;
    unsigned _iterations;
    unsigned _looped;
    // cluster id; point id = distance
    std::unordered_map<std::pair<unsigned, unsigned>, double> _distanceValues;
};

template<class Point>
KMeansAlgorithm<Point>::KMeansAlgorithm(AbstractDistance *distance,
        AbstractCentersPicker<Point> *picker,
        AbstractPointsSpace<Point> *space,
        unsigned clusters,
        unsigned iterations) :
    AbstractAlgorithm<Point>(distance, picker, space),
    _numClusters(clusters),
    _iterations(iterations)
{
}


template<class Point>
void KMeansAlgorithm<Point>::execute()
{
    this->_partition = this->_picker->performInitialPartition(
                this->_numClusters,
                this->_space);
    this->_centers = this->_picker->getInitialCentersData();
    this->_looped = 0;
    bool moved = true;
    ClusterCalculator<Point> calculator;
    unsigned centerId = 0, numPoints = this->_space->getNumOfInsertedPoints();
    unsigned assignedClusterId = 0;
    double dist = 0, currentAssignedDist;
    do
    {
        for(DensePoint* center : *(this->_centers))
        {
            for(unsigned i = 0; i < numPoints; ++i)
            {
                PtrCAbstractPoint point = this->_space->getPoint(i);
                dist = this->_distance->distance(dynamic_cast<AbstractPoint*>(center), point);
                if (this->_distanceValues.count({centerId, i}) > 0)
                    this->_distanceValues[std::make_pair(centerId, i)] = dist;
                else
                    this->_distanceValues.insert({{centerId, i}, dist});
                // this moght be a better cluster, let's check it
                assignedClusterId = this->_partition->getCluster(i);
                if (assignedClusterId == centerId)
                    continue; // if already assigned, there is no need to check
                currentAssignedDist = this->_distanceValues[std::make_pair(assignedClusterId, i)];
                if(dist < currentAssignedDist) // check if can be assigned to the curently used center
                {
                    this->_partition->assign(i, centerId); // if so, assign it
                    moved = true;
                }
            }
            ++centerId;
        }

        calculator.recalculateCenters(this->_centers, this->_partition, this->_space);
        this->_looped += 1;
        centerId = 0;
    } while(moved && this->_looped < this->_iterations);
}


#endif // KMEANSALGORITHM_H
