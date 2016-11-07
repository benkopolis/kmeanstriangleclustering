#include "abstractdistance.h"
#include <algorithm>
#include <unordered_set>

#ifndef ABSTRACTDISTANCE_CPP
#define ABSTRACTDISTANCE_CPP

AbstractDistance::AbstractDistance()
{
}

template<>
std::unordered_set<unsigned> AbstractDistance::getIntersectedIndexes(const AbstractPoint * const one, const AbstractPoint * const two) const
{
    std::unordered_set<unsigned> v(one->size() > two->size() ? one->size() : two->size());
    for(unsigned oneKey : one->getKeys()) {
        if(two->contains(oneKey))
            v.insert(oneKey);
    }

    for(unsigned twoKey : two->getKeys()) {
        if(one->contains(twoKey))
            v.insert(twoKey);
    }

    return v;
}

#endif //ABSTRACTDISTANCE_CPP
