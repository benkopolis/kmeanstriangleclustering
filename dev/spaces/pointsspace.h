#ifndef POINTSSPACE_H
#define POINTSSPACE_H

#include "abstractpointsspace.h"
#include "commons/partitiondata.h"

// This class stores all the points available in the model
class PointsSpace : public AbstractPointsSpace {
public:

    PointsSpace(unsigned num_points, unsigned num_dimensions);
    PointsSpace(const PointsSpace& another);

    virtual ~PointsSpace();

    virtual PtrCAbstractPoint operator [] (const unsigned& pid) throw(BadIndex);
    virtual PtrCAbstractPoint operator [] (const unsigned& pid) const throw(BadIndex);

    virtual void insertPoint(AbstractPoint *p, unsigned index);
    virtual PtrCAbstractPoint getPoint(unsigned index) const;
    virtual bool contains(unsigned index) const;
    virtual unsigned getNumOfInsertedPoints() const;

    virtual void savePointsSpace(const char *fileName);
    virtual PartitionData* convertTo(unsigned clusters) const;


protected:

    std::unordered_map<unsigned int, PtrCAbstractPoint> points__;
};

#endif // POINTSSPACE_H
