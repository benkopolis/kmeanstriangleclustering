#include "abstractdistance.h"
#include <algorithm>

AbstractDistance::AbstractDistance()
{
}

template<class T>
T AbstractDistance::getIntersectedIndexes(AbstractPoint *one, AbstractPoint *two)
{
    T v(one->size() > two->size() ? one->size() : two->size());
    typename T::iterator it;
    it = std::set_intersection(one->getKeys().begin(),
                               one->getKeys().end(),
                               two->getKeys().begin(),
                               two->getKeys().end(),
                               v.begin());
    v.resize(it - v.begin());

    return v;
}
