#ifndef MANHATTANDISTANCE_H
#define MANHATTANDISTANCE_H

#include "abstractdistance.h"

class ManhattanDistance : public AbstractDistance
{
public:
    ManhattanDistance();

    virtual double distance(AbstractPoint* one, AbstractPoint* two) const;
};

#endif // MANHATTANDISTANCE_H
