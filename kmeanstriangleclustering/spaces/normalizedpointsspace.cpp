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
    out << num_points__ << ' ' << num_dimensions__ << ' ' << endl;
	foreach(PointId key, points__.keys())
	{
		foreach(unsigned int dim, points__[key].keys())
            out << dim << ':' << points__[key][dim] << endl;
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
    int points=0, dimensions=0;
    in >> points >> dimensions;
	this->num_points__ = points;
	this->num_dimensions__ = dimensions;
    this->lines__ = points;
	int counter = 0, coordId=0, pointId=0, tmpPointId=0;
	Coord tmp;
	in >> pointId;
	tmpPointId = pointId;
    char separator;
    while(!in.atEnd())
	{
		Point point;
        QString line = in.readLine();
        QTextStream inner(&line);
        while(!inner.atEnd())
		{
            inner >> coordId >> separator >> tmp;
			point.insert(coordId, tmp);
		}
        points__.insert(counter++, point);
	}
	file.close();
}

QList<PointId> NormalizedPointsSpace::getPointIds() const
{
	return points__.keys();
}
