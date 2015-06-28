#ifndef ABSTRACTPOINTSSPACE_H
#define ABSTRACTPOINTSSPACE_H

#include "models.hpp"
#include "commons/abstractpoint.h"
#include "commons/utils.h"
#include "commons/sparsepoint.h"
#include "commons/densepoint.h"

template<typename T>
class AbstractPointsSpace : private Utils::Where<T, AbstractPoint>
{
public:

    virtual ~AbstractPointsSpace() {}

    virtual PtrCAbstractPoint operator [] (const unsigned& pid) throw(BadIndex) = 0;
    virtual PtrCAbstractPoint operator [] (const unsigned& pid) const throw(BadIndex) = 0;

    inline unsigned getNumPoints() const {
		return num_points__;
	}

    inline unsigned getNumDimensions() const {
		return num_dimensions__;
	}

    virtual void insertPoint(T* p, unsigned index) = 0;
    virtual PtrCAbstractPoint getPoint(unsigned index) const = 0;
    virtual bool contains(unsigned index) const = 0;

	virtual void savePointsSpace(QString fileName) = 0;
	virtual void loadPointsSpace(QString fileName) = 0;

    virtual QList<unsigned> getPointIds() const = 0;

protected:

    AbstractPointsSpace(unsigned num_points, unsigned num_dimensions);

	unsigned int num_points__;
	unsigned int num_dimensions__;

private:
};

#include "abstractpointsspace.cpp"

#endif // ABSTRACTPOINTSSPACE_H
