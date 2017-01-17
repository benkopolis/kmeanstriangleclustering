#ifndef KMEANSALGORITHM_H
#define KMEANSALGORITHM_H

#include <unordered_map>
#include <utility>
#ifdef PERFORMANCE_TEST
#include <iostream>
#include <ctime>
#include <limits>
#endif //PERFORMANCE_TEST

#ifdef DIAGNOSTICS_DEBUG
#include <iostream>
#endif //DIAGNOSTICS_DEBUG

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
#ifdef PERFORMANCE_TEST
    clock_t beginAll = clock();
    double outerAvg=0, outerMax=0, outerMin=std::numeric_limits<double>::max(),
            innerAvg=0, innerMax=0, innerMin=std::numeric_limits<double>::max(),
            tmpInner, tmpOuter, innerC=0, outerC=0;
    clock_t beginInner, beginOuter, endInner, endOuter;
#endif //PERFORMANCE_TEST
    do
    {
        for(DensePoint* center : *(this->_centers))
        {
#ifdef PERFORMANCE_TEST
           beginOuter = clock();
#endif //PERFORMANCE_TEST
            for(unsigned i = 0; i < numPoints; ++i)
            {
#ifdef PERFORMANCE_TEST
                beginInner = clock();
#endif //PERFORMANCE_TEST
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
#ifdef PERFORMANCE_TEST
                endInner = clock();
                innerC += 1;
#endif //PERFORMANCE_TEST
            }
            ++centerId;
#ifdef PERFORMANCE_TEST
            endOuter = clock();
            outerC += 1;
            tmpInner = (double)(endInner - beginInner);
            if(tmpInner > innerMax)
                innerMax = tmpInner;
            if(tmpInner < innerMin)
                innerMin = tmpInner;
            innerAvg += tmpInner;
            tmpOuter = (double)(endOuter - beginOuter);
            if(tmpOuter > outerMax)
                outerMax = tmpOuter;
            if(tmpOuter < outerMin)
                outerMin = tmpOuter;
            outerAvg += tmpOuter;
#endif //PERFORMANCE_TEST
        }

        calculator.recalculateCenters(this->_centers, this->_partition, this->_space);
#ifdef DIAGNOSTICS_DEBUG
        std::cerr << "centers ================ " << std::endl;
        for(DensePoint* p : *(this->_centers))
        {
            for(unsigned dim : p->getKeys())
            {
                std::cerr << (*p)[dim] << " ";
            }

            std::cerr << std::endl;
        }
#endif
        this->_looped += 1;
        centerId = 0;
    } while(moved && this->_looped < this->_iterations);
#ifdef PERFORMANCE_TEST
    clock_t endAll = clock();
    outerAvg = outerAvg / outerC / CLOCKS_PER_SEC;
    innerAvg = innerAvg / innerC / CLOCKS_PER_SEC;
    outerMax = outerMax / CLOCKS_PER_SEC;
    outerMin = outerMin / CLOCKS_PER_SEC;
    innerMax = innerMax / CLOCKS_PER_SEC;
    innerMin = innerMin / CLOCKS_PER_SEC;
    std::cerr << " PERFORMANCE OF KMEANS INNER LOOP BIGGER" << std::endl <<
                 "Inner Avg, min, max: " << innerAvg << " " << innerMin <<
                 " " << innerMax << std::endl << "Outer avg, min, max: " <<
                 outerAvg << " " << outerMin << " " << outerMax << std::endl <<
                 "Total execution time: " << ((double)(endAll - beginAll)) / CLOCKS_PER_SEC << std::endl;
#endif //PERFORMANCE_TEST
}


#endif // KMEANSALGORITHM_H
