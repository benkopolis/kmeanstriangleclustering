#include "densepoint.h"

volatile unsigned DensePoint::dimensions = 0;
volatile QList<unsigned> DensePoint::KEYS;
std::thread *DensePoint::keys_initializer = 0;
std::mutex DensePoint::mutex;

DensePoint::DensePoint(unsigned pid) :
    AbstractPoint(pid)
{
    this->vector = new std::vector<double>();
}

DensePoint::DensePoint(unsigned pid, unsigned nDims) :
    AbstractPoint(0)
{
    this->vector = new std::vector<double>(nDims);
}

DensePoint::~DensePoint()
{
    delete this->vector;
    this->vector = 0;
}

double & DensePoint::operator [](const unsigned& index) throw(BadIndex)
{
    if(this->vector->size() <= index)
        throw BadIndex();
    return (*this->vector)[index];
}

double DensePoint::operator [](const unsigned &index) const throw(BadIndex)
{
    if(this->vector->size() <= index)
        throw BadIndex();
    return (*this->vector)[index];
}

unsigned DensePoint::diff(const AbstractPoint *another) const throw(NotSparsePoint, NotDensePoint)
{
    return 0;
}

void DensePoint::insert(unsigned key, double value) throw(BadIndex)
{
    if(key != this->vector->size()) // insert must be called for every key from 0 to max
        throw BadIndex();
    this->vector->push_back(value);
}

const QList<unsigned> DensePoint::getKeys() const throw()
{
    if(DensePoint::keys_initializer != 0 &&
            DensePoint::keys_initializer->joinable())
    {
        DensePoint::keys_initializer->join();
        delete DensePoint::keys_initializer;
    }
    return *((QList<unsigned>*)&DensePoint::KEYS);
}

bool DensePoint::contains(unsigned pid) const throw()
{
    return this->vector->size() > pid;
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
        ((QList<unsigned>*)&DensePoint::KEYS)->append(i);
    }
}

