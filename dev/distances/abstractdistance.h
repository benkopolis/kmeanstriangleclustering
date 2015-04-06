#ifndef ABSTRACTDISTANCE_H
#define ABSTRACTDISTANCE_H

#include "commons/abstractpoint.h"

class AbstractDistance
{
public:

    virtual double distance(AbstractPoint* one, AbstractPoint* two) = 0;

protected:

    AbstractDistance();

};

#endif // ABSTRACTDISTANCE_H
