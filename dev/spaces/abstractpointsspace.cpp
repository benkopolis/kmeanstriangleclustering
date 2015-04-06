#include "abstractpointsspace.h"

template<typename T>
AbstractPointsSpace::AbstractPointsSpace()
{
}

template<typename T>
AbstractPointsSpace::AbstractPointsSpace(unsigned num_points, unsigned num_dimensions) :
	num_points__(num_points), num_dimensions__(num_dimensions)
{
}

