#ifndef POINTSSPACE_H
#define POINTSSPACE_H

#include "abstractpointsspace.h"

// This class stores all the points available in the model
//
class PointsSpace : AbstractPointsSpace {
public:

	//
	// Dump collection of points
	//
	friend std::ostream& operator <<(std::ostream& os, PointsSpace & ps) {

		PointId i = 0;
		foreach (Point p, ps.points__) {
			os << "point[" << i++ << "]=" << p << '\n';
		}
		return os;
	}

	PointsSpace(PointId num_points, Dimensions num_dimensions);

	PointsSpace(const PointsSpace& reference);

//	void dumpToFile(QString fileName);

	virtual void insertPoint(Point p, PointId index);
	virtual Point getPoint(PointId index) const;

protected:
	//
	// Init collection of points
	//
	void init_points();

	Points points__;
};

#endif // POINTSSPACE_H
