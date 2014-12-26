#ifndef ABSTRACTPOINT_H
#define ABSTRACTPOINT_H

#include "exceptions/badindex.h"
#include <QList>

class AbstractPoint
{
protected:
    AbstractPoint(unsigned pid);

    unsigned pointId;

public:

    virtual double& operator [] (const unsigned& index) throw(BadIndex) = 0;
    virtual double operator [] (const unsigned& index) const throw(BadIndex) = 0;

    virtual unsigned diff(const AbstractPoint* another) const throw() = 0;
    virtual void insert(unsigned key, double value) throw(BadIndex) = 0;
    virtual unsigned size() const throw() = 0;
    virtual const QList<unsigned>& getKeys() const throw() = 0;
};

#endif // ABSTRACTPOINT_H
