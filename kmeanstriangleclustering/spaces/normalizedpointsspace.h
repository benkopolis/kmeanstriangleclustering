#ifndef NORMALIZEDPOINTSSPACE_H
#define NORMALIZEDPOINTSSPACE_H

#include "abstractpointsspace.h"

class NormalizedPointsSpace : public AbstractPointsSpace
{
public:
    NormalizedPointsSpace();
    NormalizedPointsSpace(const NormalizedPointsSpace& another);

    virtual ~NormalizedPointsSpace() {}

    virtual void insertPoint(Point *p, PointId index);
    virtual const Point &getPoint(PointId index) const;
	virtual bool contains(PointId index) const;

	virtual void savePointsSpace(QString fileName);
	virtual void loadPointsSpace(QString fileName);
	virtual QList<PointId> getPointIds() const;

    inline void setNumberOfDimensions(unsigned int numDim) { num_dimensions__ = numDim; }
    inline void setNumberOfPoints(unsigned int numPoints) { num_points__ = numPoints; }

protected:

    QHash<PointId, Point*> points__;
	unsigned int lines__;


};

#endif // NORMALIZEDPOINTSSPACE_H
