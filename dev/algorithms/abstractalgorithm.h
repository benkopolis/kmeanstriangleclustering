#ifndef ABSTRACTALGORITHM_H
#define ABSTRACTALGORITHM_H

#include "commons/utils.h"
#include "commons/centersdata.h"
#include "commons/partitiondata.h"
#include "commons/abstractpoint.h"
#include "distances/abstractdistance.h"
#include "pickers/abstractcenterspicker.h"
#include "spaces/abstractpointsspace.h"

template<class Point, class Distance, class Picker, class Space>
class AbstractAlgorithm : private Utils::Where<Point, AbstractPoint>,
        private Utils::Where<Distance, AbstractDistance>,
        private Utils::Where<Picker, AbstractCentersPicker<Point>>,
        private Utils::Where<Space, AbstractPointsSpace<Point>>
{
public:

    virtual ~AbstractAlgorithm();

    virtual void execute() = 0;

protected:

    AbstractAlgorithm(Distance *distance,
                      Picker<Point> *picker,
                      Space<Point> *space);

protected: // fields

    AbstractDistance* _distance;
    AbstractPointsSpace<Point> * _space;
    AbstractCentersPicker<Point> * _picker;
    CentersData* _centers;
    PartitionData* _partition;


};

template<class Point, class Distance, class Picker, class Space>
AbstractAlgorithm<Point, Distance, Picker, Space>::~AbstractAlgorithm()
{
    if(this->_centers != NULL)
        delete this->_centers;
    this->_centers = NULL;

    if(this->_partition != NULL)
        delete this->_partition;
    this->_partition = NULL;
}

template<class Point, class Distance, class Picker, class Space>
AbstractAlgorithm<Point, Distance, Picker, Space>::AbstractAlgorithm(
        Distance* distance,
        Picker<Point>* picker,
        Space<Point>* space) :
    _distance(distance),
    _space(space),
    _picker(picker),
    _centers(0),
    _partition(0)
{
}


#endif // ABSTRACTALGORITHM_H
