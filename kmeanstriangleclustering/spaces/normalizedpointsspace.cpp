#include "normalizedpointsspace.h"

NormalizedPointsSpace::NormalizedPointsSpace()
{
}

void NormalizedPointsSpace::insertPoint(Point p, PointId index)
{
	points__.insert(index, p);
}

const Point NormalizedPointsSpace::getPoint(PointId index) const
{
	return points__.value(index);
}

bool NormalizedPointsSpace::contains(PointId index) const
{
	return points__.contains(index);
}

void NormalizedPointsSpace::savePointsSpace(QString fileName)
{
	QFile file(fileName);
	if(!file.open(QFile::WriteOnly))
		return;
	QTextStream out(&file);
	out << num_points__ << ' ' << num_dimensions__ << ' ' << lines__ << endl;
	foreach(PointId key, points__.keys())
	{
		foreach(unsigned int dim, points__[key].keys())
			out << key << ' ' << dim << ' ' << points__[key][dim] << endl;
	}
	out.flush();
	file.close();
}

void NormalizedPointsSpace::loadPointsSpace(QString fileName)
{
	QFile file(fileName);
	if(!file.open(QFile::ReadOnly))
		return;
	QTextStream in(&file);
	int points=0, dimensions=0, lines=0;
	in >> points >> dimensions >> lines;
	this->num_points__ = points;
	this->num_dimensions__ = dimensions;
	this->lines__ = lines;
	int counter = 0, coordId=0, pointId=0, tmpPointId=0;
	Coord tmp;
	in >> pointId;
	tmpPointId = pointId;
	while(counter < lines && !in.atEnd())
	{
		Point point;
		pointId = tmpPointId;
		while(tmpPointId == pointId)
		{
			in >> coordId;
			in >> tmp;
			point.insert(coordId, tmp);
			in >> tmpPointId;
		}
		points__.insert(counter, point);
		++counter;
	}
	file.close();
}

QList<PointId> NormalizedPointsSpace::getPointIds() const
{
	return points__.keys();
}
