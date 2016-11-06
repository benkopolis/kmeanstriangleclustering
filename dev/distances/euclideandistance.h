#ifndef EUCLIDEANDISTANCE_H
#define EUCLIDEANDISTANCE_H

#include "abstractdistance.h"
#include <unordered_set>

class EuclideanDistance : public AbstractDistance
{
public:
    EuclideanDistance();

    virtual double distance(AbstractPoint* one, AbstractPoint* two) const;

private:

    double addResultsFromSingleVector(AbstractPoint *one, const std::unordered_set<unsigned> &v, double result) const;
};

#endif // EUCLIDEANDISTANCE_H
