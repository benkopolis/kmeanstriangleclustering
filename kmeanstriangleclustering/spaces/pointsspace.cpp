#include "pointsspace.h"


PointsSpace::PointsSpace(PointId num_points, Dimensions num_dimensions) :
		AbstractPointsSpace(num_points, num_dimensions) {
	init_points();
}

PointsSpace::PointsSpace(const PointsSpace& reference) :
	AbstractPointsSpace(reference.num_points__, reference.num_dimensions__) {
	points__ = reference.points__;
}

void PointsSpace::insertPoint(Point p, PointId index)
{
	points__.insert(index, p);
	++AbstractPointsSpace::num_points__;
}

Point PointsSpace::getPoint(PointId index) const
{
	return points__.at(index);
}

void PointsSpace::init_points() {
	srand(QDateTime::currentMSecsSinceEpoch());
	for (PointId i = 0; i < num_points__; i++) {
		Point p;
		for (Dimensions d = 0; d < num_dimensions__; d++) {
			p.push_back((double)(rand() % 10)/10.0);
		}
		points__.push_back(p);

		//std::cout << "pid[" << i << "]= (" << p << ")" << std::endl;
	}
}


