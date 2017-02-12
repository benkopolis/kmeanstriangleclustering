#ifndef ABSTRACTALGORITHM_H
#define ABSTRACTALGORITHM_H

#include "commons/utils.h"
#include "commons/centersdata.h"
#include "commons/partitiondata.h"
#include "commons/abstractpoint.h"
#include "distances/abstractdistance.h"
#include "pickers/abstractcenterspicker.h"
#include "spaces/abstractpointsspace.h"

template<class Point>
class AbstractAlgorithm :
        private Utils::Where<Point, AbstractPoint>
{
public:

    virtual ~AbstractAlgorithm();

    virtual void execute() = 0;

    inline const CentersData* getCentersData() const { return this->_centers; }
    inline const PartitionData* getPartitionData() const { return this->_partition; }

protected:

    AbstractAlgorithm(AbstractDistance *distance,
                      AbstractCentersPicker<Point> *picker,
                      AbstractPointsSpace *space);

protected: // fields

    AbstractDistance* _distance;
    AbstractPointsSpace * _space;
    AbstractCentersPicker<Point> * _picker;
    CentersData* _centers;
    PartitionData* _partition;


};

template<class Point>
AbstractAlgorithm<Point>::~AbstractAlgorithm()
{
    if(this->_centers != nullptr)
        delete this->_centers;
    this->_centers = nullptr;

    if(this->_partition != nullptr)
        delete this->_partition;
    this->_partition = nullptr;
}

template<class Point>
AbstractAlgorithm<Point>::AbstractAlgorithm(AbstractDistance* distance,
        AbstractCentersPicker<Point> *picker,
        AbstractPointsSpace *space) :
    _distance(distance),
    _space(space),
    _picker(picker),
    _centers(nullptr),
    _partition(nullptr)
{
}


#endif // ABSTRACTALGORITHM_H
