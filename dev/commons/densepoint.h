#ifndef DENSEPOINT_H
#define DENSEPOINT_H

#include "abstractpoint.h"
#include "exceptions/badindex.h"
#include <vector>
#include <iostream>
#include <thread>
#include <mutex>

class DensePoint : public AbstractPoint
{
public:

    friend std::ostream& operator <<(std::ostream& os, DensePoint & dp) {

        unsigned i = 0;
        for(const double coord : dp.vector) {
            os << i << ':' << coord << ',';
            ++i;
        }
        os << std::endl;
        return os;
    }

    DensePoint(unsigned pid);
    DensePoint(unsigned pid, unsigned nDims);

    virtual double& operator [] (const unsigned& index) throw(BadIndex);
    virtual double operator [] (const unsigned& index) const throw(BadIndex);

    virtual unsigned diff(const AbstractPoint* another) const throw(NotSparsePoint, NotDensePoint);
    virtual void insert(unsigned key, double value) throw(BadIndex);
    inline virtual unsigned size() const throw() { return this->vector.size(); }
    inline virtual const QList<unsigned> getKeys() const throw();

    static void InitializeKeys(unsigned dimensions);

private:

    std::vector<double> vector;

    static volatile unsigned dimensions;
    static volatile QList<unsigned> KEYS;
    static std::thread *keys_initializer;
    static std::mutex mutex;

    static void initKeys();
};

#endif // DENSEPOINT_H
