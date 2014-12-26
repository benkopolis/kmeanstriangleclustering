#ifndef DENSEPOINT_H
#define DENSEPOINT_H

#include "abstractpoint.h"
#include "exceptions/badindex.h"
#include <vector>

class DensePoint : public AbstractPoint
{
public:
    DensePoint();

    virtual double& operator [] (const unsigned& index) throw(BadIndex);
    virtual double operator [] (const unsigned& index) const throw(BadIndex);

    virtual unsigned diff(const AbstractPoint* another) const throw();
    virtual void insert(unsigned key, double value) throw(BadIndex);
    inline virtual unsigned size() const throw() { return this->vector.size(); }
    inline virtual const QList<unsigned>& getKeys() const throw() { return QList(); }

private:

    std::vector<double> vector;
};

#endif // DENSEPOINT_H
