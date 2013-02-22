#ifndef NORMALIZEDPOINTSSPACE_H
#define NORMALIZEDPOINTSSPACE_H

#include "abstractpointsspace.h"

class NormalizedPointsSpace : public AbstractPointsSpace
{
public:
    NormalizedPointsSpace();

	virtual void insertPoint(Point p, PointId index);
	virtual Point getPoint(PointId index) const;
	virtual bool contains(PointId index) const;

	virtual void savePointsSpace(QString fileName);
	virtual void loadPointsSpace(QString fileName);
	virtual QList<PointId> getPointIds() const;

protected:

	QHash<PointId, Point> points__;
	unsigned int lines__;


};

#endif // NORMALIZEDPOINTSSPACE_H
