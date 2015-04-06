#include "pointsspace.h"

template<typename T>
PointsSpace::PointsSpace(unsigned num_points, unsigned num_dimensions) :
    AbstractPointsSpace(num_points, num_dimensions)
{

}

template<typename T>
PointsSpace::PointsSpace(const PointsSpace& another) :
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
PointsSpace::~PointsSpace()
{
    foreach(PointId index, points__.keys())
    {
        delete points__[index];
        points__[index] = 0;
    }
}

AbstractPoint *PointsSpace::operator [](const unsigned &pid) throw(BadIndex)
{
    if(!this->points__.contains(pid))
        throw BadIndex();
    return this->points__[pid];
}

const AbstractPoint *PointsSpace::operator [](const unsigned &pid) const throw(BadIndex)
{
    if(!this->points__.contains(pid))
        throw BadIndex();
    return this->points__[pid];
}

template<typename T>
void PointsSpace::insertPoint(T *p, unsigned index)
{
	points__.insert(index, p);
	++AbstractPointsSpace::num_points__;
}

template<typename T>
const AbstractPoint *PointsSpace::getPoint(unsigned index) const
{
    return points__.value(index);
}

template<typename T>
bool PointsSpace::contains(unsigned index) const
{
	return points__.contains(index);
}

template<typename T>
QList<unsigned> PointsSpace::getPointIds() const
{
	return points__.keys();
}

template<typename T>
void PointsSpace::init_points() {
	srand(QDateTime::currentMSecsSinceEpoch());
	for (PointId i = 0; i < num_points__; i++) {
        Point* p = new Point();
		for (Dimensions d = 0; d < num_dimensions__; d++) {
            p->insert(d, (double)(rand() % 10)/10.0);
		}
		points__.insert(i, p);

		//std::cout << "pid[" << i << "]= (" << p << ")" << std::endl;
	}
}

template<typename T>
void PointsSpace::savePointsSpace(QString fileName)
{
	QFile file(fileName);
	if(!file.open(QFile::WriteOnly))
		return;
	QTextStream out(&file);
	out << num_points__ << " " << num_dimensions__ << endl;
    foreach(Point* p, points__)
	{
        foreach(Coord c, *p)
            out << c << ' ';
		out << endl;
	}
    file.close();
}

template<typename T>
void PointsSpace::loadPointsSpace(QString fileName)
{
	QFile file(fileName);
	if(!file.open(QFile::ReadOnly))
		return;
	QTextStream in(&file);
	in >> num_points__;
	in >> num_dimensions__;
    for(unsigned int i=0; i<num_points__; ++i)
	{
		Coord tmp =0;
        Point* point = new Point();
        for(unsigned int j=0; j<num_dimensions__; ++j)
		{
			in >> tmp;
            point->insert(j, tmp);
		}
		points__.insert(i, point);
	}
    file.close();
}
