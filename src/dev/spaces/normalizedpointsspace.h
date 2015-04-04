#ifndef NORMALIZEDPOINTSSPACE_H
#define NORMALIZEDPOINTSSPACE_H

#include "abstractpointsspace.h"

template<typename T>
class NormalizedPointsSpace : public AbstractPointsSpace<T>
{
public:
    NormalizedPointsSpace();
    NormalizedPointsSpace(const NormalizedPointsSpace& another);

    virtual ~NormalizedPointsSpace();

    virtual AbstractPoint *operator [] (const unsigned& pid) throw(BadIndex);
    virtual AbstractPoint const *operator [] (const unsigned& pid) const throw(BadIndex);

    virtual void insertPoint(T *p, unsigned index);
    virtual const AbstractPoint *getPoint(unsigned index) const;
    virtual bool contains(unsigned index) const;

	virtual void savePointsSpace(QString fileName);
	virtual void loadPointsSpace(QString fileName);
    virtual QList<unsigned> getPointIds() const;

protected:

    QHash<unsigned, AbstractPoint*> points__;
	unsigned int lines__;


};

#endif // NORMALIZEDPOINTSSPACE_H
