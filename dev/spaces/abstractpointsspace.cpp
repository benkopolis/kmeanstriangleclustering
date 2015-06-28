#include "abstractpointsspace.h"

#ifndef ABSTRACTPOINTSPACE_CPP
#define ABSTRACTPOINTSPACE_CPP

template<typename T>
AbstractPointsSpace<T>::AbstractPointsSpace(unsigned num_points, unsigned num_dimensions) :
	num_points__(num_points), num_dimensions__(num_dimensions)
{
}

#endif //ABSTRACTPOINTSPACE_CPP

