#ifndef EUCLIDEANDISTANCE_H
#define EUCLIDEANDISTANCE_H

#include "abstractdistance.h"
#include <unordered_set>

class EuclideanDistance : public AbstractDistance
{
public:
    EuclideanDistance();

    virtual double distance(AbstractPoint* one, AbstractPoint* two);

private:

    double addResultsFromSingleVector(AbstractPoint *one, const std::unordered_set<unsigned> &v, double result);
};

#endif // EUCLIDEANDISTANCE_H
