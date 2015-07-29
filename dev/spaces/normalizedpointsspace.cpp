#include "normalizedpointsspace.h"

#ifndef NORMALIZEDPOINTSPACE_CPP
#define NORMALIZEDPOINTSPACE_CPP

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

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
            point->insert({j, src.value(j)});
        points__.insert({i, dynamic_cast<AbstractPoint*>(point)});
    }
}

template<typename T>
NormalizedPointsSpace<T>::~NormalizedPointsSpace()
{
    for(auto pair : points__)
    {
        delete points__[pair.first];
        points__[pair.first] = 0;
    }
}

template<typename T>
PtrCAbstractPoint NormalizedPointsSpace<T>::operator [](const unsigned &pid) throw(BadIndex)
{
    if(this->points__.count(pid) == 0)
        throw BadIndex();
    return this->points__[pid];
}

template<typename T>
PtrCAbstractPoint NormalizedPointsSpace<T>::operator [](const unsigned &pid) const throw(BadIndex)
{
    if(!this->points__.count(pid) == 0)
        throw BadIndex();
    return this->points__.at(pid);
}

template<typename T>
void NormalizedPointsSpace<T>::insertPoint(T *p, unsigned index)
{
    points__.insert({index, p});
}

template<typename T>
PtrCAbstractPoint NormalizedPointsSpace<T>::getPoint(unsigned index) const
{
    return this->points__.at(index);
}

template<typename T>
bool NormalizedPointsSpace<T>::contains(unsigned index) const
{
    return points__.count(index) > 0;
}

template<typename T>
void NormalizedPointsSpace<T>::savePointsSpace(const char* fileName)
{
    std::ofstream out(fileName, std::ios::out | std::ios::trunc);
    if(!out.is_open())
		return;
    out << this->num_points__ << ' ' << this->num_dimensions__ << ' ' << std::endl;
    for(auto point : this->points__)
	{
        for(unsigned dim : points__[point.first]->getKeys())
            out << dim << ':' << (*points__[point.first])[dim] << std::endl;
	}

	out.flush();
    out.close();
}

template<typename T>
void NormalizedPointsSpace<T>::loadPointsSpace(const char* fileName)
{
    std::ifstream in(fileName);
    if(!in.is_open())
		return;
    in >> this->num_points__ >> this->num_dimensions__ >> this->quant;
    this->lines__ = this->num_points__;
    int counter = 0, coordId=0, pointId=0;
	Coord tmp;
	in >> pointId;
    char separator;
    while(!in.eof())
	{
        T* point = new T(counter);
        std::string line;
        std::getline(in, line);
        std::stringstream inner(std::ios::in);
        inner.str(line);
        inner.seekg(0, std::ios_base::beg);
        while(!inner.eof())
		{
            inner >> coordId >> separator >> tmp;
            point->insert(coordId, tmp);
		}
        points__.insert({counter, dynamic_cast<AbstractPoint*>(point)});
	}
    in.close();
}


#endif //NORMALIZEDPOINTSPACE_CPP
