#include "pointsspace.h"

#ifndef POINTSPACE_CPP
#define POINTSPACE_CPP

#include "commons/partitiondata.h"
#include "commons/densepoint.h"
#include "commons/sparsepoint.h"

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

PointsSpace::PointsSpace(unsigned num_points, unsigned num_dimensions) :
    AbstractPointsSpace(num_points, num_dimensions)
{

}

PointsSpace::PointsSpace(const PointsSpace& another) :
    AbstractPointsSpace(another.num_points__, another.num_dimensions__)
{
    for(unsigned int i=0; i < this->num_points__; ++i)
    {
        AbstractPoint* point = nullptr;
        PtrCAbstractPoint src = another.getPoint(i);
        if (typeid(src) == typeid(DensePoint))
            point = new DensePoint(i);
        else if (typeid(src) == typeid(SparsePoint))
            point = new SparsePoint(i);
        else throw 1;
        for(unsigned int j=0; j < this->num_dimensions__; ++j)
        {
            if(src->contains(j))
                point->insert(j, src->get(j));
        }
        points__.insert({i, point});
    }
}

PointsSpace::~PointsSpace()
{
    for(auto pair: points__)
    {
        delete points__[pair.first];
        points__[pair.first] = 0;
    }
}

PtrCAbstractPoint PointsSpace::operator [](const unsigned &pid) throw(BadIndex)
{
    if(this->points__.count(pid) == 0)
        throw BadIndex(__FILE__, __LINE__);
    return this->points__[pid];
}

PtrCAbstractPoint PointsSpace::operator [](const unsigned &pid) const throw(BadIndex)
{
    if(this->points__.count(pid) == 0)
        throw BadIndex(__FILE__, __LINE__);
    return this->points__.at(pid);
}

void PointsSpace::insertPoint(AbstractPoint *p, unsigned index)
{
    this->points__.insert({index, p});
}

PtrCAbstractPoint PointsSpace::getPoint(unsigned index) const
{
    return this->points__.at(index);
}

bool PointsSpace::contains(unsigned index) const
{
    return this->points__.count(index) > 0;
}

unsigned PointsSpace::getNumOfInsertedPoints() const
{
    return this->points__.size();
}

void PointsSpace::savePointsSpace(const char* fileName)
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

PartitionData *PointsSpace::convertTo(unsigned clusters) const
{
    throw clusters;
}

#endif //POINTSPACE_CPP
