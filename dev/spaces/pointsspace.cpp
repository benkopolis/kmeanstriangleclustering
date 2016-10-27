#include "pointsspace.h"

#ifndef POINTSPACE_CPP
#define POINTSPACE_CPP

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

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
        points__.insert({i, dynamic_cast<PtrCAbstractPoint>(point)});
    }
}

template<typename T>
PointsSpace<T>::~PointsSpace()
{
    for(auto pair: points__)
    {
        delete points__[pair.first];
        points__[pair.first] = 0;
    }
}

template<typename T>
PtrCAbstractPoint PointsSpace<T>::operator [](const unsigned &pid) throw(BadIndex)
{
    if(this->points__.count(pid) == 0)
        throw BadIndex(__FILE__, __LINE__);
    return this->points__[pid];
}

template<typename T>
PtrCAbstractPoint PointsSpace<T>::operator [](const unsigned &pid) const throw(BadIndex)
{
    if(this->points__.count(pid) == 0)
        throw BadIndex(__FILE__, __LINE__);
    return this->points__.at(pid);
}

template<typename T>
void PointsSpace<T>::insertPoint(T *p, unsigned index)
{
    this->points__.insert({index, p});
}

template<typename T>
PtrCAbstractPoint PointsSpace<T>::getPoint(unsigned index) const
{
    return this->points__.at(index);
}

template<typename T>
bool PointsSpace<T>::contains(unsigned index) const
{
    return this->points__.count(index) > 0;
}

template<typename T>
unsigned PointsSpace<T>::getNumOfInsertedPoints() const
{
    return this->points__.size();
}

template<typename T>
void PointsSpace<T>::savePointsSpace(const char* fileName)
{
    std::ofstream out(fileName, std::ios::out | std::ios::trunc);
    if(!out.is_open())
		return;
    out << this->num_points__ << " " << this->num_dimensions__ << this->quant << std::endl;
    for(auto p : points__)
	{
        for(unsigned i : p.second->getKeys())
            out << (*p.second)[i] << ' ';
        out << std::endl;
	}
    out.close();
}

template<typename T>
void PointsSpace<T>::loadPointsSpace(const char* fileName)
{
    std::ifstream in(fileName, std::ios::in);
    if(!in.is_open())
        return;
    in >> this->num_points__;
    in >> this->num_dimensions__;
    in >> this->quant;
    for(unsigned int i=0; i<this->num_points__; ++i)
	{
		Coord tmp =0;
        T* point = new T(i);
        for(unsigned int j=0; j<this->num_dimensions__; ++j)
		{
			in >> tmp;
            point->insert(j, tmp);
		}
        points__.insert({i, dynamic_cast<PtrCAbstractPoint>(point)});
	}
    in.close();
}

#endif //POINTSPACE_CPP
