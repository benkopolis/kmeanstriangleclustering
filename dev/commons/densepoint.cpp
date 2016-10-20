#include "densepoint.h"
#include <typeinfo>
#include <typeindex>

unsigned DensePoint::dimensions = 0;
std::future<std::list<unsigned>*> DensePoint::KEYS;
std::list<unsigned>* DensePoint::KEYS_RETURNED = 0;
std::thread *DensePoint::keys_initializer = 0;
bool DensePoint::initialized = false;

DensePoint::DensePoint(unsigned pid) throw(DimensionsNotSet) :
    AbstractPoint(pid)
{
    if(dimensions == 0)
        throw DimensionsNotSet(__FILE__, __LINE__);
    this->vector = new std::vector<double>(dimensions);
}

DensePoint::DensePoint(unsigned pid, unsigned nDims) throw(DimensionsNotSet, BadIndex) :
    AbstractPoint(pid)
{
    if(dimensions == 0)
        throw DimensionsNotSet(__FILE__, __LINE__);
    if(nDims > dimensions)
        throw BadIndex("You're trying to create DensePoint with different dimensions then set globally", __FILE__, __LINE__);
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
        throw BadIndex("Point with given index is not held by the object.", __FILE__, __LINE__);
    return (*this->vector)[index];
}

double DensePoint::operator [](const unsigned &index) const throw(BadIndex)
{
    if(this->vector->size() <= index)
        throw BadIndex("Point with given index is not held by the object.", __FILE__, __LINE__);
    return (*this->vector)[index];
}

unsigned DensePoint::diff(const AbstractPoint *another, bool exact = false) const throw(NotSparsePoint, NotDensePoint)
{
    if(!exact)
        return 0;

    if(another == 0 || std::type_index(typeid(*another)) != std::type_index(typeid(DensePoint)))
        throw NotDensePoint(__FILE__, __LINE__);

    unsigned difference = 0;
    for(int i = 0; i < this->vector->size(); ++i)
    {
        if(this->vector->at(i) != (*another)[i])
            ++difference;
    }
    return difference;
}

void DensePoint::insert(unsigned key, double value) throw(BadIndex)
{
    if(key != this->vector->size() && this->vector->size() < dimensions) // insert must be called for every key from 0 to max
        throw BadIndex("Dimension was skipped while inserting values into DensPoint.", __FILE__, __LINE__);
    if(key >= dimensions)
        throw BadIndex("Given key to insert coordinate value exceeds DensePoint:dimensions.", __FILE__, __LINE__);
    if(this->vector->size() < dimensions)
        this->vector->push_back(value);
    else if(key < this->vector->size())
        (*this->vector)[key] = value;
    else
        throw BadIndex("This is not supported way of inserting a value for given index.", __FILE__, __LINE__);
}

const std::list<unsigned>& DensePoint::getKeys() const throw(DimensionsNotSet)
{
    if(!initialized)
        throw new DimensionsNotSet("GetKeys can't be called before initilizing all keys!", __FILE__, __LINE__);

    if(KEYS_RETURNED != NULL)
        return *KEYS_RETURNED;

    KEYS.wait();
    KEYS_RETURNED = KEYS.get();
    return *KEYS_RETURNED;
}

bool DensePoint::contains(unsigned pid) const throw()
{
    return this->vector->size() > pid;
}

double DensePoint::get(const unsigned &index) const throw(BadIndex)
{
    if(index >= this->vector->size())
        throw BadIndex("Point with given index is not held by the object.", __FILE__, __LINE__);
    return (*this->vector)[index];
}

void DensePoint::InitializeKeys(unsigned numD)
{
    dimensions = numD;
    if (initialized == true && KEYS_RETURNED != 0)
        delete KEYS_RETURNED;
    else
        initialized = true;
    KEYS = std::async(std::launch::async, initKeys);
}

std::list<unsigned> *DensePoint::initKeys()
{
    std::list<unsigned>* result = new std::list<unsigned>();
    for(unsigned i = 0; i < dimensions; ++i)
    {
        result->push_back(i);
    }

    return result;
}

