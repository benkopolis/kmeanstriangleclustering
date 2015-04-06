#include "pointsspace.h"

template<typename T>
PointsSpace<T>::PointsSpace(unsigned num_points, unsigned num_dimensions) :
    AbstractPointsSpace<T>(num_points, num_dimensions)
{

}

template<typename T>
PointsSpace<T>::PointsSpace(const PointsSpace& another) :
    AbstractPointsSpace<T>(another.num_points__, another.num_dimensions__)
{
    for(unsigned int i=0; i < this->num_points__; ++i)
    {
        T* point = new T(i);
        const T& src = another.getPoint(i);
        for(unsigned int j=0; j < this->num_dimensions__; ++j)
            point->insert(j, src.value(j));
        points__.insert(i, dynamic_cast<AbstractPoint*>(point));
    }
}

template<typename T>
PointsSpace<T>::~PointsSpace()
{
    foreach(PointId index, points__.keys())
    {
        delete points__[index];
        points__[index] = 0;
    }
}

template<typename T>
AbstractPoint *PointsSpace<T>::operator [](const unsigned &pid) throw(BadIndex)
{
    if(!this->points__.contains(pid))
        throw BadIndex();
    return this->points__[pid];
}

template<typename T>
const AbstractPoint *PointsSpace<T>::operator [](const unsigned &pid) const throw(BadIndex)
{
    if(!this->points__.contains(pid))
        throw BadIndex();
    return this->points__[pid];
}

template<typename T>
void PointsSpace<T>::insertPoint(T *p, unsigned index)
{
	points__.insert(index, p);
    ++(this->num_points__);
}

template<typename T>
const AbstractPoint *PointsSpace<T>::getPoint(unsigned index) const
{
    return points__.value(index);
}

template<typename T>
bool PointsSpace<T>::contains(unsigned index) const
{
	return points__.contains(index);
}

template<typename T>
QList<unsigned> PointsSpace<T>::getPointIds() const
{
	return points__.keys();
}

template<typename T>
void PointsSpace<T>::init_points() {
	srand(QDateTime::currentMSecsSinceEpoch());
    for (PointId i = 0; i < this->num_points__; i++) {
        T* p = new T(i);
        for (Dimensions d = 0; d < this->num_dimensions__; d++) {
            p->insert(d, (double)(rand() % 10)/10.0);
		}
        points__.insert(i, dynamic_cast<AbstractPoint*>(p));

		//std::cout << "pid[" << i << "]= (" << p << ")" << std::endl;
	}
}

template<typename T>
void PointsSpace<T>::savePointsSpace(QString fileName)
{
	QFile file(fileName);
	if(!file.open(QFile::WriteOnly))
		return;
	QTextStream out(&file);
    out << this->num_points__ << " " << this->num_dimensions__ << endl;
    foreach(Point* p, points__)
	{
        foreach(Coord c, *p)
            out << c << ' ';
		out << endl;
	}
    file.close();
}

template<typename T>
void PointsSpace<T>::loadPointsSpace(QString fileName)
{
	QFile file(fileName);
	if(!file.open(QFile::ReadOnly))
		return;
	QTextStream in(&file);
    in >> this->num_points__;
    in >> this->num_dimensions__;
    for(unsigned int i=0; i<this->num_points__; ++i)
	{
		Coord tmp =0;
        T* point = new T();
        for(unsigned int j=0; j<this->num_dimensions__; ++j)
		{
			in >> tmp;
            point->insert(j, tmp);
		}
        points__.insert(i, dynamic_cast<AbstractPoint*>(point));
	}
    file.close();
}
