#include "normalizedpointsspace.h"

#ifndef NORMALIZEDPOINTSPACE_CPP
#define NORMALIZEDPOINTSPACE_CPP

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

NormalizedPointsSpace::NormalizedPointsSpace(unsigned num_points, unsigned num_dimensions) :
    AbstractPointsSpace(num_points, num_dimensions)
{
    this->_convertedTo = nullptr;
}

NormalizedPointsSpace::NormalizedPointsSpace(const NormalizedPointsSpace& another) :
    AbstractPointsSpace(another.num_points__, another.num_dimensions__)
{
    this->_convertedTo = nullptr;
    for(unsigned int i=0; i<this->num_points__; ++i)
    {
        AbstractPoint* point = nullptr;
        PtrCAbstractPoint src = another.getPoint(i);
        if (typeid(src) == typeid(DensePoint))
            point = new DensePoint(i);
        else if (typeid(src) == typeid(SparsePoint))
            point = new SparsePoint(i);
        else throw 1;
        for(unsigned int j=0; j<this->num_dimensions__; ++j)
            point->insert(j, src->get(j));
        points__.insert({i, point});
    }
}

NormalizedPointsSpace::~NormalizedPointsSpace()
{
    for(auto pair : points__)
    {
        delete points__[pair.first];
        points__[pair.first] = 0;
    }

    delete this->_convertedTo;
}

PtrCAbstractPoint NormalizedPointsSpace::operator [](const unsigned &pid) throw(BadIndex)
{
    if(this->points__.count(pid) == 0)
        throw BadIndex(__FILE__, __LINE__);
    return this->points__[pid];
}

PtrCAbstractPoint NormalizedPointsSpace::operator [](const unsigned &pid) const throw(BadIndex)
{
    if(!this->points__.count(pid) == 0)
        throw BadIndex(__FILE__, __LINE__);
    return this->points__.at(pid);
}

void NormalizedPointsSpace::insertPoint(AbstractPoint *p, unsigned index)
{
    points__.insert({index, p});
}

PtrCAbstractPoint NormalizedPointsSpace::getPoint(unsigned index) const
{
    return this->points__.at(index);
}

bool NormalizedPointsSpace::contains(unsigned index) const
{
    return this->points__.count(index) > 0;
}

unsigned NormalizedPointsSpace::getNumOfInsertedPoints() const
{
    return this->points__.size();
}

void NormalizedPointsSpace::savePointsSpace(const char* fileName)
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

PartitionData *NormalizedPointsSpace::convertTo(unsigned clusters) const
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
