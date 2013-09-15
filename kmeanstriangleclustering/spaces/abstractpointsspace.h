#ifndef ABSTRACTPOINTSSPACE_H
#define ABSTRACTPOINTSSPACE_H

#include "models.hpp"

class AbstractPointsSpace
{
public:

    virtual ~AbstractPointsSpace() {}

    inline PointId getNumPoints() const {
		return num_points__;
	}

    inline PointId getNumDimensions() const {
		return num_dimensions__;
	}

	virtual void insertPoint(Point p, PointId index) = 0;
	virtual const Point getPoint(PointId index) const = 0;
	virtual bool contains(PointId index) const = 0;

	virtual void savePointsSpace(QString fileName) = 0;
	virtual void loadPointsSpace(QString fileName) = 0;

	virtual QList<PointId> getPointIds() const = 0;

protected:


	AbstractPointsSpace();
	AbstractPointsSpace(PointId num_points, Dimensions num_dimensions);


	unsigned int num_points__;
	unsigned int num_dimensions__;
};

#endif // ABSTRACTPOINTSSPACE_H
