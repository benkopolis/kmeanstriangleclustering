#ifndef HAMILTONDISTANCE_H
#define HAMILTONDISTANCE_H

#include "abstractdistance.h"

class HamiltonDistance : public AbstractDistance
{
public:
    HamiltonDistance();

    virtual double distance(AbstractPoint* one, AbstractPoint* two);
};

#endif // HAMILTONDISTANCE_H
