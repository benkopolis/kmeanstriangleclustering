#include "hamiltondistance.h"
#include <vector>
#include <algorithm>

HamiltonDistance::HamiltonDistance()
{
}

double HamiltonDistance::distance(AbstractPoint *one, AbstractPoint *two)
{
    std::vector<unsigned> v(one->size() + two->size());
    std::vector<unsigned>::iterator it;

    std::set_union(one->getKeys().begin(),
                   one->getKeys().end(),
                   two->getKeys().begin(),
                   two->getKeys().end(),
                   v.begin());

    v.resize(it - v.begin());
    std::vector<unsigned> u = this->getIntersectedIndexes<std::vector<unsigned> >(one, two);
    return v.size() - u.size();
}
