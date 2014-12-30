#include "densepoint.h"

unsigned DensePoint::dimensions = 0;
QList<unsigned> DensePoint::KEYS;
std::thread *DensePoint::keys_initializer = 0;
std::mutex DensePoint::mutex;

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

const QList<unsigned> &DensePoint::getKeys() const
{
    if(DensePoint::keys_initializer != 0 &&
            DensePoint::keys_initializer->joinable())
    {
        DensePoint::keys_initializer->join();
        delete DensePoint::keys_initializer;
    }
    return DensePoint::KEYS;
}

void DensePoint::InitializeKeys(unsigned dimensions)
{
    mutex.lock();
    DensePoint::keys_initializer = new std::thread(DensePoint::initKeys);
    mutex.unlock();
}

void DensePoint::initKeys()
{
    for(unsigned i = 0; i < DensePoint::dimensions; ++i)
    {
        DensePoint::KEYS.append(i);
    }
}

