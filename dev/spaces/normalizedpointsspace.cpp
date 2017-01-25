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
    this->_convertedTo = nullptr;
}

template<typename T>
NormalizedPointsSpace<T>::NormalizedPointsSpace(const NormalizedPointsSpace& another) :
    AbstractPointsSpace<T>(another.num_points__, another.num_dimensions__)
{
    this->_convertedTo = nullptr;
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

    delete this->_convertedTo;
}

template<typename T>
PtrCAbstractPoint NormalizedPointsSpace<T>::operator [](const unsigned &pid) throw(BadIndex)
{
    if(this->points__.count(pid) == 0)
        throw BadIndex(__FILE__, __LINE__);
    return this->points__[pid];
}

template<typename T>
PtrCAbstractPoint NormalizedPointsSpace<T>::operator [](const unsigned &pid) const throw(BadIndex)
{
    if(!this->points__.count(pid) == 0)
        throw BadIndex(__FILE__, __LINE__);
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
    return this->points__.count(index) > 0;
}

template<typename T>
unsigned NormalizedPointsSpace<T>::getNumOfInsertedPoints() const
{
    return this->points__.size();
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
PartitionData *NormalizedPointsSpace<T>::convertTo(unsigned clusters) const
{
    if (this->_convertedTo != nullptr)
        return this->_convertedTo;
    unsigned num_of_iters = 0;
    PartitionData* data = new PartitionData(clusters, this->num_points__);
    std::unordered_map<unsigned, PtrCAbstractPoint>::const_iterator ii = this->points__.begin();
    while(ii != this->points__.end())
    {
        PtrCAbstractPoint tmp = ii->second;
        unsigned fileId = tmp->getArbitraryClusterId();
        unsigned pointId = ii->first;
        data->assign_unsafe(pointId, fileId);
        ++ii;
        ++num_of_iters;
    }

    this->_convertedTo = data;
    if (num_of_iters > this->points__.size())
        throw 1;
    return data;
}


#endif //NORMALIZEDPOINTSPACE_CPP
