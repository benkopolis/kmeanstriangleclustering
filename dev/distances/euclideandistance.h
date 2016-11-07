#ifndef EUCLIDEANDISTANCE_H
#define EUCLIDEANDISTANCE_H

#include "abstractdistance.h"
#include <unordered_set>

class EuclideanDistance : public AbstractDistance
{
public:
    EuclideanDistance();

    virtual double distance(const AbstractPoint * const one, const AbstractPoint * const two) const;

private:

    double addResultsFromSingleVector(const AbstractPoint * const one, const std::unordered_set<unsigned> &v, double result) const;
};

#endif // EUCLIDEANDISTANCE_H
