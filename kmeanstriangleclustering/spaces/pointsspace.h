#ifndef POINTSSPACE_H
#define POINTSSPACE_H

#include "abstractpointsspace.h"

// This class stores all the points available in the model
//
class PointsSpace : public AbstractPointsSpace {
public:

    PointsSpace();

    PointsSpace(const PointsSpace& another);

    virtual ~PointsSpace();

	PointsSpace(PointId num_points, Dimensions num_dimensions);

//	void dumpToFile(QString fileName);

    virtual void insertPoint(AbstractPoint* p, unsigned index);
    virtual const AbstractPoint *getPoint(unsigned index) const;
    virtual bool contains(unsigned index) const;

	virtual void savePointsSpace(QString fileName);
	virtual void loadPointsSpace(QString fileName);
    virtual QList<unsigned> getPointIds() const;


protected:
	//
	// Init collection of points
	//
	void init_points();

    QHash<unsigned int, AbstractPoint*> points__;
};

#endif // POINTSSPACE_H
