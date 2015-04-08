#ifndef VECTOR_H
#define VECTOR_H

#include <QVector>
#include <QHash>
#include "abstractpoint.h"
#include "exceptions/badindex.h"
#include "exceptions/notsparsepoint.h"

class SparsePoint : public AbstractPoint
{
public:

    friend std::ostream& operator <<(std::ostream& os, SparsePoint & dp) {
        for(const unsigned i : dp.hash->keys()) {
            os << i << ':' << (*dp.hash)[i] << ',';
        }
        os << std::endl;
        return os;
    }

    SparsePoint(unsigned pid);
    virtual ~SparsePoint();

    virtual double& operator [] (const unsigned& index) throw(BadIndex);
    virtual double operator [] (const unsigned& index) const throw(BadIndex);

    virtual unsigned diff(const AbstractPoint* another) const throw(NotSparsePoint, NotDensePoint);
    virtual void insert(unsigned key, double value) throw(BadIndex);
    inline virtual unsigned size() const throw() { return this->hash->size(); }
    inline virtual const QList<unsigned> getKeys() const throw();
    virtual bool contains(unsigned pid) const throw();

private:

    QHash<unsigned, double> * hash;
};

Q_DECLARE_TYPEINFO(SparsePoint, Q_MOVABLE_TYPE);

#endif // VECTOR_H
