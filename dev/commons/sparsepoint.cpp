#include <list>
#include <typeinfo>
#include <algorithm>
#include <functional>
#include <typeindex>
#include "sparsepoint.h"

SparsePoint::SparsePoint(unsigned pid) :
    AbstractPoint(pid)
{
    this->hash = new std::unordered_map<unsigned, double>();
    this->keys = new std::list<unsigned>();
}

SparsePoint::~SparsePoint()
{
    delete this->hash;
    this->hash = 0;
    delete this->keys;
    this->keys = 0;
}

double& SparsePoint::operator [](const unsigned& index) throw(BadIndex)
{
    if(this->hash->find(index) == this->hash->end())
        throw BadIndex();
    return (*this->hash)[index];
}

double SparsePoint::operator [](const unsigned &index) const throw(BadIndex)
{
    if(this->hash->find(index) == this->hash->end())
        throw BadIndex();
    return (*this->hash)[index];
}

unsigned SparsePoint::diff(const AbstractPoint* another, bool exact = false) const throw(NotSparsePoint, NotDensePoint)
{
    if(another == 0 || std::type_index(typeid(*another)) != std::type_index(typeid(SparsePoint)))
        throw NotSparsePoint();
    const SparsePoint* p = dynamic_cast<const SparsePoint*>(another);
    unsigned difference = 0;
    bool itBigger = this->hash->size() > p->hash->size();
    std::unordered_map<unsigned, double> *bigger = itBigger ?
                this->hash : p->hash;
    std::unordered_map<unsigned, double>* local = itBigger ?
                p->hash : this->hash;
    typename std::unordered_map<unsigned, double>::const_iterator foundValue;
    for(auto i: *bigger)
    {
        if((foundValue = local->find(i.first)) == local->end())
            ++difference;
        else if(exact && foundValue->second != i.second)
            ++difference;
    }

    return itBigger ? difference + this->hash->size() - p->hash->size() :
                      difference + p->hash->size() - this->hash->size();
}

void SparsePoint::insert(unsigned key, double value) throw(BadIndex)
{
    this->hash->insert({key, value});
    this->keys->push_back(key);
}

const std::list<unsigned>& SparsePoint::getKeys() const throw(DimensionsNotSet)
{
    this->keys->sort(std::less<unsigned>());
    return *(this->keys);
}

bool SparsePoint::contains(unsigned pid) const throw()
{
    return this->hash->count(pid) > 0;
}

