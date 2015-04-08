#ifndef ABSTRACTPOINT_H
#define ABSTRACTPOINT_H

#include "exceptions/badindex.h"
#include "exceptions/notdensepoint.h"
#include "exceptions/notsparsepoint.h"
#include <QList>

class AbstractPoint
{
protected:
    AbstractPoint(unsigned pid);

    unsigned pointId;

public:

    virtual double& operator [] (const unsigned& index) throw(BadIndex) = 0;
    virtual double operator [] (const unsigned& index) const throw(BadIndex) = 0;

    virtual unsigned diff(const AbstractPoint* another) const throw(NotSparsePoint, NotDensePoint) = 0;
    virtual void insert(unsigned key, double value) throw(BadIndex) = 0;
    virtual unsigned size() const throw() = 0;
    virtual bool contains(unsigned pid) const throw() = 0;

    /**
     * @brief getKeys method returns list of unsigned values representing indexes of point coordinates.
     * @param fileName is the name of the text file with point space in a proper format.
     * @param container - the points' space object.
     * @return Sorted list of point's coordinates' indexes.
     *
     * The list is always sorted! From smaller to bigger.
     */
    virtual const QList<unsigned> getKeys() const throw() = 0;
};

Q_DECLARE_TYPEINFO(AbstractPoint, Q_MOVABLE_TYPE);

typedef AbstractPoint const * const CPtrCAbstractPoint;

typedef AbstractPoint const * PtrCAbstractPoint;

#endif // ABSTRACTPOINT_H
