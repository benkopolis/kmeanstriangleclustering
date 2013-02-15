#include "abstractpointsspace.h"

AbstractPointsSpace::AbstractPointsSpace()
{
}

AbstractPointsSpace::AbstractPointsSpace(PointId num_points, Dimensions num_dimensions) :
	num_points__(num_points), num_dimensions__(num_dimensions)
{
}

