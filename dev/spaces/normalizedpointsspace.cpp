#include "normalizedpointsspace.h"

template<typename T>
NormalizedPointsSpace<T>::NormalizedPointsSpace(unsigned num_points, unsigned num_dimensions) :
    AbstractPointsSpace<T>(num_points, num_dimensions)
{
}

template<typename T>
NormalizedPointsSpace<T>::NormalizedPointsSpace(const NormalizedPointsSpace& another) :
    AbstractPointsSpace<T>(another.num_points__, another.num_dimensions__)
{
    for(unsigned int i=0; i<this->num_points__; ++i)
    {
        T* point = new T(i);
        const T* src = another.getPoint(i);
        for(unsigned int j=0; j<this->num_dimensions__; ++j)
            point->insert(j, src.value(j));
        points__.insert(i, dynamic_cast<AbstractPoint*>(point));
    }
}

template<typename T>
NormalizedPointsSpace<T>::~NormalizedPointsSpace()
{
    foreach(PointId index, points__.keys())
    {
        delete points__[index];
        points__[index] = 0;
    }
}

template<typename T>
AbstractPoint *NormalizedPointsSpace<T>::operator [](const unsigned &pid) throw(BadIndex)
{
    if(!this->points__.contains(pid))
        throw BadIndex();
    return this->points__[pid];
}

template<typename T>
const AbstractPoint *NormalizedPointsSpace<T>::operator [](const unsigned &pid) const throw(BadIndex)
{
    if(!this->points__.contains(pid))
        throw BadIndex();
    return this->points__[pid];
}

template<typename T>
void NormalizedPointsSpace<T>::insertPoint(T *p, unsigned index)
{
	points__.insert(index, p);
}

template<typename T>
const AbstractPoint *NormalizedPointsSpace<T>::getPoint(unsigned index) const
{
    return *points__.value(index);
}

template<typename T>
bool NormalizedPointsSpace<T>::contains(unsigned index) const
{
	return points__.contains(index);
}

template<typename T>
void NormalizedPointsSpace<T>::savePointsSpace(QString fileName)
{
	QFile file(fileName);
	if(!file.open(QFile::WriteOnly))
		return;
	QTextStream out(&file);
    out << this->num_points__ << ' ' << this->num_dimensions__ << ' ' << endl;
	foreach(PointId key, points__.keys())
	{
        for(unsigned dim : points__[key]->getKeys())
            out << dim << ':' << (*points__[key])[dim] << endl;
	}
	out.flush();
	file.close();
}

template<typename T>
void NormalizedPointsSpace<T>::loadPointsSpace(QString fileName)
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
        T* point = new T(counter);
        QString line = in.readLine();
        QTextStream inner(&line);
        while(!inner.atEnd())
		{
            inner >> coordId >> separator >> tmp;
            point->insert(coordId, tmp);
		}
        points__.insert(counter++, dynamic_cast<AbstractPoint*>(point));
	}
	file.close();
}

template<typename T>
QList<unsigned> NormalizedPointsSpace<T>::getPointIds() const
{
	return points__.keys();
}
