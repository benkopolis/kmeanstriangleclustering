#ifndef NORMALIZEDPOINTSSPACE_H
#define NORMALIZEDPOINTSSPACE_H

#include "abstractpointsspace.h"

class NormalizedPointsSpace : public AbstractPointsSpace
{
public:
    NormalizedPointsSpace();

	virtual void insertPoint(Point p, PointId index) = 0;
	virtual Point getPoint(PointId index) = 0;

protected:


};

#endif // NORMALIZEDPOINTSSPACE_H
