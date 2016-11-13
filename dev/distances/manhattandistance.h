#ifndef MANHATTANDISTANCE_H
#define MANHATTANDISTANCE_H

#include "abstractdistance.h"

class ManhattanDistance : public AbstractDistance
{
public:
    ManhattanDistance();
    virtual ~ManhattanDistance();

    virtual double distance(const AbstractPoint * const one, const AbstractPoint * const two) const;
};

#endif // MANHATTANDISTANCE_H
