#ifndef NORMALIZEDPOINTSSPACE_H
#define NORMALIZEDPOINTSSPACE_H

#include "abstractpointsspace.h"

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

	virtual void savePointsSpace(QString fileName);
	virtual void loadPointsSpace(QString fileName);
    virtual QList<unsigned> getPointIds() const;

protected:

    QHash<unsigned, PtrCAbstractPoint> points__;
	unsigned int lines__;

private:

};

#include "normalizedpointsspace.cpp"

#endif // NORMALIZEDPOINTSSPACE_H
