#ifndef HAMILTONDISTANCE_H
#define HAMILTONDISTANCE_H

#include "abstractdistance.h"

class HamiltonDistance : public AbstractDistance
{
public:
    HamiltonDistance();
    virtual ~HamiltonDistance();

    virtual double distance(const AbstractPoint * const one, const AbstractPoint * const two) const;
};

#endif // HAMILTONDISTANCE_H
