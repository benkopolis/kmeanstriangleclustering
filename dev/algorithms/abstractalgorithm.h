#ifndef ABSTRACTALGORITHM_H
#define ABSTRACTALGORITHM_H

#include "commons/utils.h"
#include "commons/centersdata.h"
#include "commons/partitiondata.h"
#include "commons/abstractpoint.h"
#include "distances/abstractdistance.h"
#include "pickers/abstractcenterspicker.h"
#include "spaces/abstractpointsspace.h"

template<class Point, class Distance>
class AbstractAlgorithm :
        private Utils::Where<Distance, AbstractDistance>,
        private Utils::Where<Point, AbstractPoint>
{
public:

    virtual ~AbstractAlgorithm();

    virtual void execute() = 0;

    inline const CentersData* getCentersData() const { return this->_centers; }
    inline const PartitionData* getPartitionData() const { return this->_partition; }

protected:

    AbstractAlgorithm(Distance *distance,
                      AbstractCentersPicker<Point> *picker,
                      AbstractPointsSpace<Point> *space);

protected: // fields

    AbstractDistance* _distance;
    AbstractPointsSpace<Point> * _space;
    AbstractCentersPicker<Point> * _picker;
    CentersData* _centers;
    PartitionData* _partition;


};

template<class Point, class Distance>
AbstractAlgorithm<Point, Distance>::~AbstractAlgorithm()
{
    if(this->_centers != NULL)
        delete this->_centers;
    this->_centers = NULL;

    if(this->_partition != NULL)
        delete this->_partition;
    this->_partition = NULL;
}

template<class Point, class Distance>
AbstractAlgorithm<Point, Distance>::AbstractAlgorithm(Distance* distance,
        AbstractCentersPicker<Point> *picker,
        AbstractPointsSpace<Point> *space) :
    _distance(distance),
    _space(space),
    _picker(picker),
    _centers(0),
    _partition(0)
{
}


#endif // ABSTRACTALGORITHM_H
