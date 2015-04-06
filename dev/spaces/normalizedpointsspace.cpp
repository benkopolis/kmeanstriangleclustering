#include "normalizedpointsspace.h"

template<typename T>
NormalizedPointsSpace::NormalizedPointsSpace()
{
}

template<typename T>
NormalizedPointsSpace::NormalizedPointsSpace(const NormalizedPointsSpace& another) :
    AbstractPointsSpace(another.num_points__, another.num_dimensions__)
{
    for(unsigned int i=0; i<num_points__; ++i)
    {
        Point* point = new Point();
        const Point& src = another.getPoint(i);
        for(unsigned int j=0; j<num_dimensions__; ++j)
            point->insert(j, src.value(j));
        points__.insert(i, point);
    }
}

template<typename T>
NormalizedPointsSpace::~NormalizedPointsSpace()
{
    foreach(PointId index, points__.keys())
    {
        delete points__[index];
        points__[index] = 0;
    }
}

template<typename T>
AbstractPoint *NormalizedPointsSpace::operator [](const unsigned &pid) throw(BadIndex)
{
    if(!this->points__.contains(pid))
        throw BadIndex();
    return this->points__[pid];
}

const AbstractPoint *NormalizedPointsSpace::operator [](const unsigned &pid) const throw(BadIndex)
{
    if(!this->points__.contains(pid))
        throw BadIndex();
    return this->points__[pid];
}

template<typename T>
void NormalizedPointsSpace::insertPoint(T *p, unsigned index)
{
	points__.insert(index, p);
}

template<typename T>
const AbstractPoint *NormalizedPointsSpace::getPoint(unsigned index) const
{
    return *points__.value(index);
}

template<typename T>
bool NormalizedPointsSpace::contains(unsigned index) const
{
	return points__.contains(index);
}

template<typename T>
void NormalizedPointsSpace::savePointsSpace(QString fileName)
{
	QFile file(fileName);
	if(!file.open(QFile::WriteOnly))
		return;
	QTextStream out(&file);
    out << num_points__ << ' ' << num_dimensions__ << ' ' << endl;
	foreach(PointId key, points__.keys())
	{
        foreach(unsigned int dim, points__[key]->keys())
            out << dim << ':' << (*points__[key])[dim] << endl;
	}
	out.flush();
	file.close();
}

template<typename T>
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
    int counter = 0, coordId=0, pointId=0;
	Coord tmp;
	in >> pointId;
    char separator;
    while(!in.atEnd())
	{
        Point* point = new Point();
        QString line = in.readLine();
        QTextStream inner(&line);
        while(!inner.atEnd())
		{
            inner >> coordId >> separator >> tmp;
            point->insert(coordId, tmp);
		}
        points__.insert(counter++, point);
	}
	file.close();
}

template<typename T>
QList<unsigned> NormalizedPointsSpace::getPointIds() const
{
	return points__.keys();
}
