#ifndef NORMALIZEDPOINTSSPACE_H
#define NORMALIZEDPOINTSSPACE_H

#include "abstractpointsspace.h"

class NormalizedPointsSpace : public AbstractPointsSpace
{
public:
    NormalizedPointsSpace();
    NormalizedPointsSpace(const NormalizedPointsSpace& another);

    virtual ~NormalizedPointsSpace();

    virtual void insertPoint(AbstractPoint *p, unsigned index);
    virtual const AbstractPoint *getPoint(unsigned index) const;
    virtual bool contains(unsigned index) const;

	virtual void savePointsSpace(QString fileName);
	virtual void loadPointsSpace(QString fileName);
    virtual QList<unsigned> getPointIds() const;

    inline void setNumberOfDimensions(unsigned int numDim) { num_dimensions__ = numDim; }
    inline void setNumberOfPoints(unsigned int numPoints) { num_points__ = numPoints; }

protected:

    QHash<unsigned, AbstractPoint*> points__;
	unsigned int lines__;


};

#endif // NORMALIZEDPOINTSSPACE_H
