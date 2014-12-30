#ifndef ABSTRACTPOINTSSPACE_H
#define ABSTRACTPOINTSSPACE_H

#include "models.hpp"
#include "commons/abstractpoint.h"

class AbstractPointsSpace
{
public:

    virtual ~AbstractPointsSpace() {}

    inline unsigned getNumPoints() const {
		return num_points__;
	}

    inline unsigned getNumDimensions() const {
		return num_dimensions__;
	}

    virtual void insertPoint(AbstractPoint* p, unsigned index) = 0;
    virtual const AbstractPoint& getPoint(unsigned index) const = 0;
    virtual bool contains(unsigned index) const = 0;

	virtual void savePointsSpace(QString fileName) = 0;
	virtual void loadPointsSpace(QString fileName) = 0;

    virtual QList<unsigned> getPointIds() const = 0;

protected:


	AbstractPointsSpace();
    AbstractPointsSpace(unsigned num_points, unsigned num_dimensions);


	unsigned int num_points__;
	unsigned int num_dimensions__;
};

#endif // ABSTRACTPOINTSSPACE_H
