#ifndef RANDOMCENTERPICKER_H
#define RANDOMCENTERPICKER_H

#include <random>
#include <functional>

#include "abstractcenterspicker.h"
#include "commons/centersdata.h"

template<typename PointType>
class RandomCenterPicker : public AbstractCentersPicker<PointType>
{
public:
    RandomCenterPicker()
    {
        this->_clustersDistribution = NULL;
    }

    virtual ~RandomCenterPicker()
    {
        if (this->_clustersDistribution != NULL)
            delete this->_clustersDistribution;
    }

    virtual PartitionData *performInitialPartition(unsigned clusters, AbstractPointsSpace* ps)
    {
        PartitionData* data = new PartitionData(clusters, ps->getDeclaredNumPoints());
        this->initialData = new CentersData(clusters);
        this->_clustersDistribution = new std::uniform_int_distribution<unsigned>(0, clusters - 1);
        this->_clusterId = std::bind(*(this->_clustersDistribution), this->_generator);
        unsigned cid;
        for (unsigned pid = 0; pid < ps->getDeclaredNumPoints(); pid++)
        {
            cid = this->_clusterId();
            data->assign_unsafe(pid, cid);
            this->addCoordsToCenter(ps->getPoint(pid), cid);
        }

        this->divideCentersCoords(data);

        return data;
    }

private:

    std::function<unsigned()> _clusterId;
    std::uniform_int_distribution<unsigned>* _clustersDistribution;
    std::default_random_engine _generator;
};

#endif // RANDOMCENTERPICKER_H
