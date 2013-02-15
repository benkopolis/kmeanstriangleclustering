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
		foreach (Point p, ps.points__.values()) {
			os << "point[" << i++ << "]=" << p << '\n';
		}
		return os;
	}

	PointsSpace();

	PointsSpace(PointId num_points, Dimensions num_dimensions);

	PointsSpace(const PointsSpace& reference);

//	void dumpToFile(QString fileName);

	virtual void insertPoint(Point p, PointId index);
	virtual Point getPoint(PointId index) const;

	virtual void savePointsSpace(QString fileName);
	virtual void loadPointsSpace(QString fileName);


protected:
	//
	// Init collection of points
	//
	void init_points();

	QHash<unsigned int, Point> points__;
};

#endif // POINTSSPACE_H
