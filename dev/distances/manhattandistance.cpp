#include "manhattandistance.h"
#include <vector>
#include <algorithm>

ManhattanDistance::ManhattanDistance()
{
}

ManhattanDistance::~ManhattanDistance()
{
}

double ManhattanDistance::distance(const AbstractPoint * const one, const AbstractPoint * const two) const
{
    std::vector<unsigned> v(one->size() + two->size());
    std::vector<unsigned>::iterator it;

    it = std::set_union(one->getKeys().begin(),
                   one->getKeys().end(),
                   two->getKeys().begin(),
                   two->getKeys().end(),
                   v.begin());

    v.resize(it - v.begin());
    std::vector<unsigned> u = this->getIntersectedIndexes<std::vector<unsigned> >(one, two);
    return v.size() - u.size();
}

