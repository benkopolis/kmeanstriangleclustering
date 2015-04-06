#include <QList>
#include <typeinfo>
#include <algorithm>
#include <functional>
#include <typeindex>
#include "sparsepoint.h"

SparsePoint::SparsePoint(unsigned pid) :
    AbstractPoint(pid)
{
    this->hash = new QHash<unsigned, double>();
}

SparsePoint::~SparsePoint()
{
    delete this->hash;
    this->hash = 0;
}

double& SparsePoint::operator [](const unsigned& index) throw(BadIndex)
{
    if(!this->hash->contains(index))
        throw BadIndex();
    return (*this->hash)[index];
}

double SparsePoint::operator [](const unsigned &index) const throw(BadIndex)
{
    if(!this->hash->contains(index))
        throw BadIndex();
    return (*this->hash)[index];
}

unsigned SparsePoint::diff(const AbstractPoint* another) const throw(NotSparsePoint, NotDensePoint)
{
    if(std::type_index(typeid(*another)) != std::type_index(typeid(SparsePoint)))
        throw NotSparsePoint();
    const SparsePoint* p = dynamic_cast<const SparsePoint*>(another);
    unsigned diff = 0;
    bool itBigger = this->hash->size() > p->hash->size();
    QList<unsigned> keys = itBigger ?
                this->hash->keys() : p->hash->keys();
    QHash<unsigned, double>* local = itBigger ?
                p->hash : this->hash;
    for(const unsigned& i: keys)
    {
        if(!local->contains(i))
            ++diff;
    }
    return itBigger ? diff + this->hash->size() - p->hash->size() :
                      diff + p->hash->size() - this->hash->size();
}

void SparsePoint::insert(unsigned key, double value) throw(BadIndex)
{
    this->hash->insert(key, value);
}

const QList<unsigned> SparsePoint::getKeys() const throw()
{
    QList<unsigned> list = this->hash->keys();
    std::sort(list.begin(), list.end(), std::less<unsigned>());
    return list;
}

bool SparsePoint::contains(unsigned pid) const throw()
{
    return this->hash->contains(pid);
}

