#include "abstractpointsspace.h"

#ifndef ABSTRACTPOINTSPACE_CPP
#define ABSTRACTPOINTSPACE_CPP

template<class T>
AbstractPointsSpace<T>::AbstractPointsSpace(unsigned num_points, unsigned num_dimensions) :
    num_points__(num_points), num_dimensions__(num_dimensions), quant(0)
{
}

template<class T>
double AbstractPointsSpace<T>::getQuant() const
{
    return this->quant;
}

template<class T>
void AbstractPointsSpace<T>::setQuant(double value)
{
    this->quant = value;
}


#endif //ABSTRACTPOINTSPACE_CPP

