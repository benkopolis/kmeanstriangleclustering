#include "densepoint.h"

DensePoint::DensePoint()
{
}

double & DensePoint::operator [](const unsigned& index)
{
    if(!this->hash.contains(index))
        throw BadIndex();
    return this->values[index];
}

double DensePoint::operator [](const unsigned &index) const
{
    if(!this->hash.contains(index))
        throw BadIndex();
    return this->values[index];
}

unsigned DensePoint::diff(const AbstractPoint *another) const
{
    return 0;
}

void DensePoint::insert(unsigned key, double value)
{
    if(key != this->vector.size()) // insert must be called for every key form 0 to max
        throw BadIndex();
    this->vector.push_back(value);
}
