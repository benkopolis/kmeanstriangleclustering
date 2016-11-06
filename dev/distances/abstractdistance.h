#ifndef ABSTRACTDISTANCE_H
#define ABSTRACTDISTANCE_H

#include "commons/abstractpoint.h"
#include <unordered_set>
#include <algorithm>

class AbstractDistance
{
public:

    virtual double distance(AbstractPoint* one, AbstractPoint* two) const = 0;

protected:

    AbstractDistance();

    template<class T>
    T getIntersectedIndexes(AbstractPoint *one, AbstractPoint *two) const;

};

template<>
std::unordered_set<unsigned> AbstractDistance::getIntersectedIndexes(AbstractPoint *one, AbstractPoint *two) const;

template<class T>
T AbstractDistance::getIntersectedIndexes(AbstractPoint *one, AbstractPoint *two) const
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


#endif // ABSTRACTDISTANCE_H
