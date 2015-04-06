#ifndef ABSTRACTDISTANCE_H
#define ABSTRACTDISTANCE_H

#include "commons/abstractpoint.h"

class AbstractDistance
{
public:

    virtual double distance(AbstractPoint* one, AbstractPoint* two) = 0;

protected:

    AbstractDistance();

    template<class T>
    T getIntersectedIndexes(AbstractPoint *one, AbstractPoint *two);

};

#endif // ABSTRACTDISTANCE_H
