#ifndef DIMENSIONBASEDCENTERSPICKER_H
#define DIMENSIONBASEDCENTERSPICKER_H

#include <map>
#include <unordered_set>
#include <limits>

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

    virtual PartitionData *performInitialPartition(unsigned clusters, AbstractPointsSpace<PointType>* ps)
    {
        PartitionData* data = new PartitionData(clusters, ps->getDeclaredNumPoints());
        this->initialData = new CentersData(clusters);
        ManhattanDistance distance;
        unsigned dist = 0, totalDist = 0, minDist = std::numeric_limits<unsigned>::max();
        unsigned numPoints = ps->getNumOfInsertedPoints();
        for(unsigned pid1 = 0; pid1 < numPoints - 1; ++pid1)
        {
            for(unsigned pid2 = pid1 + 1; pid2< numPoints; ++pid2)
            {
                dist = static_cast<unsigned>(distance.distance(ps->getPoint(pid1), ps->getPoint(pid2)) + 0.5);
                if(dist < minDist)
                    minDist = dist;
                this->_distances.insert({{pid1, pid2}, dist});
                totalDist = totalDist + dist;
            } // now we are finished with total dist for this point

            unsigned reversedPid2 = pid1 - 1;
            while(reversedPid2 > -1 && reversedPid2 < pid1)
            {
                totalDist = totalDist + this->_distances[std::make_pair(reversedPid2, pid1)];
                --reversedPid2;
            }

            this->_distanceToPoint.insert({totalDist, pid1});
        }

        unsigned gensClusters = 0;
        std::unordered_multiset<std::pair<unsigned, unsigned>, unsigned>::iterator theDist;
        std::multimap<unsigned, unsigned>::iterator theTotal = this->_distanceToPoint.begin();
        std::pair<unsigned, unsigned> keyForDist;
        std::vector<std::multimap<unsigned, unsigned>::iterator> seeds;
        while(this->_distances.size() > 0)
        {
            while(data->is_assigned(theTotal.second))
                ++theTotal;
            if (!data->is_assigned(theTotal.second))
            {
                data->assign_unsafe(theTotal.second, gensClusters);
                seeds.push_back(theTotal);
            }
            else
                theTotal = seeds[gensClusters];
            for(unsigned pid = 0; pid < numPoints - 1; ++pid)
            {
                if (pid == theTotal.second)
                    continue;
                if (pid < theTotal.second)
                    keyForDist = std::make_pair(pid, theTotal.second);
                else
                    keyForDist = std::make_pair(theTotal.second, pid);
                theDist = this->_distances.find(keyForDist);
                while (theDist.first.first == theTotal.second && theDist.first.second == pid)
                {
                    if (theDist.second == minDist)
                    {
                        data->assign_unsafe(pid, gensClusters);
                        theDist = this->_distances.erase(theDist);
                    }
                    else
                        ++theDist;
                }
            }

            ++gensClusters;
            if(gensClusters == clusters)
            {
                gensClusters = 0;
                minDist = minDist + 1;
            }
        }

        return data;
    }

private:

    std::multimap<unsigned, unsigned> _distanceToPoint;
    std::unordered_multiset<std::pair<unsigned, unsigned>, unsigned> _distances;
}

#endif // DIMENSIONBASEDCENTERSPICKER_H

