#ifndef ABSTRACTPOINTSSPACE_H
#define ABSTRACTPOINTSSPACE_H

#include "models.hpp"

class AbstractPointsSpace
{
public:

	inline const PointId getNumPoints() const {
		return num_points__;
	}

	inline const PointId getNumDimensions() const {
		return num_dimensions__;
	}

	virtual void insertPoint(Point p, PointId index) = 0;
	virtual Point getPoint(PointId index) const = 0;

protected:


	AbstractPointsSpace();
	AbstractPointsSpace(PointId num_points, Dimensions num_dimensions);


	unsigned int num_points__;
	unsigned int num_dimensions__;
};

#endif // ABSTRACTPOINTSSPACE_H
