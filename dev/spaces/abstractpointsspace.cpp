#include "abstractpointsspace.h"

#ifndef ABSTRACTPOINTSPACE_CPP
#define ABSTRACTPOINTSPACE_CPP

template<typename T>
AbstractPointsSpace<T>::AbstractPointsSpace(unsigned num_points, unsigned num_dimensions) :
    num_points__(num_points), num_dimensions__(num_dimensions), quant(0)
{
}

template<typename T>
double AbstractPointsSpace<T>::getQuant() const
{
    return this->quant;
}

template<typename T>
void AbstractPointsSpace<T>::setQuant(double value)
{
    this->quant = value;
}


#endif //ABSTRACTPOINTSPACE_CPP

