#ifndef NORMALIZEDPOINTSSPACE_H
#define NORMALIZEDPOINTSSPACE_H

#include "abstractpointsspace.h"
#include "commons/partitiondata.h"
#include "exceptions/invalidconversiontype.h"

#include <string>
#include <typeinfo>
#include <unordered_map>

template<typename T>
class NormalizedPointsSpace : public AbstractPointsSpace<T>
{
public:
    NormalizedPointsSpace(unsigned num_points, unsigned num_dimensions);
    NormalizedPointsSpace(const NormalizedPointsSpace& another);

    virtual ~NormalizedPointsSpace();

    virtual PtrCAbstractPoint operator [](const unsigned& pid) throw(BadIndex);
    virtual PtrCAbstractPoint operator [](const unsigned& pid) const throw(BadIndex);

    virtual void insertPoint(T *p, unsigned index);
    virtual PtrCAbstractPoint getPoint(unsigned index) const;
    virtual bool contains(unsigned index) const;
    virtual unsigned getNumOfInsertedPoints() const;

    virtual void savePointsSpace(const char *fileName);

    virtual PartitionData* convertTo(unsigned clusters) const;

protected:

    std::unordered_map<unsigned, PtrCAbstractPoint> points__;
	unsigned int lines__;

private:

    mutable PartitionData* _convertedTo;

};

#include "normalizedpointsspace.cpp"

#endif // NORMALIZEDPOINTSSPACE_H
