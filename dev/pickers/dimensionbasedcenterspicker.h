#ifndef DIMENSIONBASEDCENTERSPICKER_H
#define DIMENSIONBASEDCENTERSPICKER_H

#include <map>
#include <unordered_map>
#include <limits>
#include <set>
#include <utility>
#include <iostream>

#include "abstractcenterspicker.h"
#include "commons/abstractpoint.h"
#include "distances/manhattandistance.h"
#include "commons/pair_hash.h"

template <class PointType>
class DimensionBasedCentersPicker: public AbstractCentersPicker<PointType>
{
public:

    DimensionBasedCentersPicker() { }

    virtual ~DimensionBasedCentersPicker() {}

    virtual PartitionData *performInitialPartition(unsigned clusters, AbstractPointsSpace<PointType>* ps);

private:

    std::multimap<unsigned, unsigned> _distanceToPoint;
    std::unordered_map<unsigned, unsigned> _pointToDistance;
    std::unordered_map<std::pair<unsigned, unsigned>, unsigned> _distances;
};

template <class PointType>
PartitionData *DimensionBasedCentersPicker<PointType>::performInitialPartition(unsigned clusters, AbstractPointsSpace<PointType> *ps)
{
    PartitionData* data = new PartitionData(clusters, ps->getDeclaredNumPoints());
    this->initialData = new CentersData(clusters);
    ManhattanDistance distance;
    std::set<unsigned> distValues;
    unsigned dist = 0, totalDist = 0, minDist = std::numeric_limits<unsigned>::max();
    unsigned numPoints = ps->getNumOfInsertedPoints();
    for(unsigned pid1 = 0; pid1 < numPoints - 1; ++pid1)
    {
        for(unsigned pid2 = pid1 + 1; pid2< numPoints; ++pid2)
        {
            dist = static_cast<unsigned>(distance.distance(ps->getPoint(pid1), ps->getPoint(pid2)) + 0.5);
            if(distValues.count(dist) == 0)
                distValues.insert(dist);
            if(dist < minDist)
                minDist = dist;
            this->_distances.insert({{pid1, pid2}, dist});
            totalDist = totalDist + dist;
        }

        unsigned reversedPid2 = pid1 - 1;
        while(reversedPid2 >= 0 && reversedPid2 < pid1)
        {
            totalDist = totalDist + this->_distances[std::make_pair(reversedPid2, pid1)];
            --reversedPid2;
        } // now we are finished with total dist for this point

        this->_distanceToPoint.insert({totalDist, pid1});
        this->_pointToDistance.insert({pid1, totalDist});
        totalDist = 0;
    }

    unsigned gensClusters = 0, currentPid = 0;
    std::multimap<unsigned, unsigned>::iterator theTotal;
    std::set<unsigned>::const_iterator currMinDist = distValues.cbegin();
    std::cerr << "MinDist initial: " << *currMinDist << std::endl;
    std::vector<unsigned> seeds;
    std::pair<unsigned, unsigned> keyForDist;
    unsigned loopCount = 0, innerLoop = 0;
    while(data->assigned_points() < ps->getNumOfInsertedPoints())
    {
        theTotal = this->_distanceToPoint.begin();
        if (theTotal != this->_distanceToPoint.end()
                && seeds.size() < clusters
                && !data->is_assigned(theTotal->second))
        {
            data->assign_unsafe(theTotal->second, gensClusters);
            this->_pointToDistance.erase(theTotal->second);
            currentPid = theTotal->second;
            this->_distanceToPoint.erase(theTotal);
            seeds.push_back(currentPid);
        }
        else
            currentPid = seeds[gensClusters];
        for(unsigned pid = 0; pid < numPoints; ++pid)
        {
            if (pid == currentPid || data->is_assigned(pid))
                continue;
            if (pid < currentPid)
                keyForDist = std::make_pair(pid, currentPid);
            else
                keyForDist = std::make_pair(currentPid, pid);
            dist = this->_distances[keyForDist];
            if (dist <= *currMinDist)
            {
                data->assign_unsafe(pid, gensClusters);
                totalDist = this->_pointToDistance[pid];
                this->_pointToDistance.erase(pid);
                this->_distanceToPoint.erase(totalDist);
            }
            ++innerLoop;
        }

        ++gensClusters;
        ++loopCount;
        if(gensClusters == clusters)
        {
            gensClusters = 0;
            ++currMinDist;
            std::cerr << "MinDist increased: " << *currMinDist << std::endl
                      << "Looped in while: " << loopCount << std::endl
                      << "Looped in for: " << innerLoop << std::endl;
        }
    }

    return data;
}

#endif // DIMENSIONBASEDCENTERSPICKER_H

