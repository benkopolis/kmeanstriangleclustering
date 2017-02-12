#include "abstractpointsspace.h"

#ifndef ABSTRACTPOINTSPACE_CPP
#define ABSTRACTPOINTSPACE_CPP

AbstractPointsSpace::AbstractPointsSpace(unsigned num_points, unsigned num_dimensions) :
    num_points__(num_points), num_dimensions__(num_dimensions), quant(0)
{
}

double AbstractPointsSpace::getQuant() const
{
    return this->quant;
}

void AbstractPointsSpace::setQuant(double value)
{
    this->quant = value;
}


#endif //ABSTRACTPOINTSPACE_CPP

