#ifndef DENSEPOINT_H
#define DENSEPOINT_H

#include "abstractpoint.h"
#include "exceptions/badindex.h"
#include "exceptions/dimensionsnotset.h"
#include <vector>
#include <iostream>
#include <future>
#include <thread>
#include <mutex>

class DensePoint : public AbstractPoint
{
public:

    friend std::ostream& operator <<(std::ostream& os, DensePoint & dp) {

        unsigned i = 0;
        for(const double coord : *dp.vector) {
            os << i << ':' << coord << ',';
            ++i;
        }
        os << std::endl;
        return os;
    }

    DensePoint(unsigned pid) throw(DimensionsNotSet);
    DensePoint(unsigned pid, unsigned nDims) throw(DimensionsNotSet, BadIndex);
    virtual ~DensePoint();

    virtual double& operator [] (const unsigned& index) throw(BadIndex);
    virtual double operator [] (const unsigned& index) const throw(BadIndex);

    virtual unsigned diff(const AbstractPoint* another, bool exact) const throw(NotSparsePoint, NotDensePoint);

    virtual void insert(unsigned key, double value) throw(BadIndex);

    inline virtual unsigned size() const throw() { return this->vector->size(); }

    virtual const std::list<unsigned> &getKeys() const throw(DimensionsNotSet);

    virtual bool contains(unsigned dimIndex) const throw();

    virtual double get(const unsigned& index) const throw(BadIndex);

    static void InitializeKeys(unsigned numD);

private:

    std::vector<double>* vector;

    static unsigned dimensions;
    static std::future<std::list<unsigned>*> KEYS;
    static std::list<unsigned>* KEYS_RETURNED;
    static std::thread *keys_initializer;
    static bool initialized;

    static std::list<unsigned> *initKeys();
};

#endif // DENSEPOINT_H
