#include "pointsspace.h"

PointsSpace::PointsSpace()
{

}

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
	return points__.value(index);
}

void PointsSpace::init_points() {
	srand(QDateTime::currentMSecsSinceEpoch());
	for (PointId i = 0; i < num_points__; i++) {
		Point p;
		for (Dimensions d = 0; d < num_dimensions__; d++) {
			p.push_back((double)(rand() % 10)/10.0);
		}
		points__.insert(i, p);

		//std::cout << "pid[" << i << "]= (" << p << ")" << std::endl;
	}
}

void PointsSpace::savePointsSpace(QString fileName)
{
	QFile file(fileName);
	if(!file.open(QFile::WriteOnly))
		return;
	QTextStream out(&file);
	out << num_points__ << " " << num_dimensions__ << endl;
	foreach(Point p, points__)
	{
		foreach(Coord c, p)
			out << c << " ";
		out << endl;
	}
}

void PointsSpace::loadPointsSpace(QString fileName)
{
	QFile file(fileName);
	if(!file.open(QFile::ReadOnly))
		return;
	QTextStream in(&file);
	in >> num_points__;
	in >> num_dimensions__;
	for(int i=0; i<num_points__; ++i)
	{
		Coord tmp =0;
		Point point;
		for(int j=0; j<num_dimensions__; ++j)
		{
			in >> tmp;
			point.push_back(tmp);
		}
		points__.insert(i, point);
	}
}


