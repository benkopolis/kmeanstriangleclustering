#include "euclideandistance.h"
#include <unordered_set>

EuclideanDistance::EuclideanDistance()
{
}

EuclideanDistance::~EuclideanDistance()
{
}

double EuclideanDistance::distance(const AbstractPoint * const one, const AbstractPoint * const two) const
{
    std::unordered_set<unsigned> v = this->getIntersectedIndexes<std::unordered_set<unsigned> >(one, two);
    double result = 0.0;
    for(unsigned i : v) {
        result = result + pow(fabs((*one)[i] - (*two)[i]), 2.0); // fabs in case of Y is not exactly 2
    }

    result = this->addResultsFromSingleVector(one, v, result);
    result = this->addResultsFromSingleVector(two, v, result);

    return sqrt(result);
}

double EuclideanDistance::addResultsFromSingleVector(const AbstractPoint * const one, const std::unordered_set<unsigned> &v, double result) const
{
    for(unsigned i : one->getKeys()) {
        if(v.find(i) == v.end())
            result = result + pow((*one)[i], 2.0);
    }

    return result;
}
