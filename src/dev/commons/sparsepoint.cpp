#include <QList>
#include "sparsepoint.h"

SparsePoint::Vector()
{
    this->hash = new QHash<unsigned, double>();
}

SparsePoint::~SparsePoint()
{
    delete this->hash;
    this->hash = 0;
}

double& SparsePoint::operator [](const unsigned& index)
{
    if(!this->hash->contains(index))
        throw BadIndex();
    return this->values[index];
}

double SparsePoint::operator [](const unsigned &index) const
{
    if(!this->hash->contains(index))
        throw BadIndex();
    return this->values[index];
}

unsigned SparsePoint::diff(const AbstractPoint* another) const
{
    SparsePoint* p = dynamic_cast<SparsePoint*>(another);
    if(!p)
        throw NotSparsePoint();
    unsigned diff = 0;
    bool itBigger = this->hash->size() > p->hash->size();
    QList<unsigned> keys = itBigger ?
                this->hash->keys() : p->hash->keys();
    QHash<unsigned, double>& local = itBigger ?
                p->hash : this->hash;
    for(const unsigned& i: keys)
    {
        if(!local.contains(i))
            ++diff;
    }
    return itBigger ? diff + this->hash->size() - p->hash->size() :
                      diff + p->hash->size() - this->hash->size();
}

void SparsePoint::insert(unsigned key, double value)
{
    this->hash->insert(key, value);
}

