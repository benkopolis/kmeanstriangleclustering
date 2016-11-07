#include "hamiltondistance.h"
#include <vector>
#include <algorithm>

HamiltonDistance::HamiltonDistance()
{
}

double HamiltonDistance::distance(const AbstractPoint * const one, const AbstractPoint * const two) const
{
    std::unordered_set<unsigned> v = this->getIntersectedIndexes<std::unordered_set<unsigned> >(one, two);
    double result = 0.0;
    for(unsigned i : v) {
        result = result + fabs((*one)[i] - (*two)[i]); // fabs in case of Y is not exactly 2
    }

    for(unsigned i : one->getKeys()) {
        if(v.count(i) > 0)
            continue;
        result = result + (*one)[i];
    }

    for(unsigned i : two->getKeys()) {
        if(v.count(i) > 0)
            continue;
        result = result + (*two)[i];
    }

    return result;
}
