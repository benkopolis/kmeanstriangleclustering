#ifndef ABSTRACTPOINTSSPACE_H
#define ABSTRACTPOINTSSPACE_H

#include "models.hpp"
#include "commons/abstractpoint.h"
#include "commons/utils.h"
#include "commons/sparsepoint.h"
#include "commons/densepoint.h"
#include "commons/partitiondata.h"

#include <list>

class AbstractPointsSpace
{
public:

    virtual ~AbstractPointsSpace() {}

    virtual PtrCAbstractPoint operator [] (const unsigned& pid) throw(BadIndex) = 0;
    virtual PtrCAbstractPoint operator [] (const unsigned& pid) const throw(BadIndex) = 0;

    inline unsigned getDeclaredNumPoints() const {
		return num_points__;
	}

    inline unsigned getNumDimensions() const {
		return num_dimensions__;
	}

    virtual void insertPoint(AbstractPoint* p, unsigned index) = 0;
    virtual PtrCAbstractPoint getPoint(unsigned index) const = 0;
    virtual bool contains(unsigned index) const = 0;
    virtual unsigned getNumOfInsertedPoints() const = 0;

    virtual void savePointsSpace(const char* fileName) = 0;
    virtual PartitionData* convertTo(unsigned clusters) const = 0;

    double getQuant() const;
    void setQuant(double value);

protected:

    AbstractPointsSpace(unsigned num_points, unsigned num_dimensions);

	unsigned int num_points__;
	unsigned int num_dimensions__;

    double quant;

};

#endif // ABSTRACTPOINTSSPACE_H
