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
        private utils::Where<Distance, AbstractDistance>,
        private Utils::Where<Picker, AbstractCentersPicker>,
        private Utils::Where<Space, AbstractPointsSpace>
{
public:

    virtual void execute() = 0;

protected:

    AbstractAlgorithm();

protected: // fields


};

#endif // ABSTRACTALGORITHM_H
