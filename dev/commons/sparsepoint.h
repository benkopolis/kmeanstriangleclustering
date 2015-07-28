#ifndef VECTOR_H
#define VECTOR_H

#include "abstractpoint.h"
#include "exceptions/badindex.h"
#include "exceptions/notsparsepoint.h"

#include <unordered_map>

class SparsePoint : public AbstractPoint
{
public:

    friend std::ostream& operator <<(std::ostream& os, SparsePoint & dp) {
        for(auto i : *dp.hash) {
            os << i.first << ':' << i.second << ',';
        }
        os << std::endl;
        return os;
    }

    SparsePoint(unsigned pid);
    virtual ~SparsePoint();

    virtual double& operator [] (const unsigned& index) throw(BadIndex);
    virtual double operator [] (const unsigned& index) const throw(BadIndex);

    virtual unsigned diff(const AbstractPoint* another, bool exact) const throw(NotSparsePoint, NotDensePoint);
    virtual void insert(unsigned key, double value) throw(BadIndex);
    inline virtual unsigned size() const throw() { return this->hash->size(); }
    virtual bool contains(unsigned pid) const throw();

    inline virtual const QList<unsigned> getKeys() const throw(DimensionsNotSet);

private:

    std::unordered_map<unsigned, double> * hash;
    QList<unsigned> * keys;
};

Q_DECLARE_TYPEINFO(SparsePoint, Q_MOVABLE_TYPE);

#endif // VECTOR_H
