#include "densepoint.h"
#include <typeinfo>
#include <typeindex>

unsigned DensePoint::dimensions = 0;
std::future<QList<unsigned>*> DensePoint::KEYS;
std::thread *DensePoint::keys_initializer = 0;
bool DensePoint::initialized = false;

DensePoint::DensePoint(unsigned pid) throw(DimensionsNotSet) :
    AbstractPoint(pid)
{
    if(dimensions == 0)
        throw DimensionsNotSet();
    this->vector = new std::vector<double>(dimensions);
}

DensePoint::DensePoint(unsigned pid, unsigned nDims) throw(DimensionsNotSet, BadIndex) :
    AbstractPoint(pid)
{
    if(dimensions == 0)
        throw DimensionsNotSet();
    if(nDims != dimensions)
        throw BadIndex("You're trying to create DensePoint with different dimensions then set globally");
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

unsigned DensePoint::diff(const AbstractPoint *another, bool exact = false) const throw(NotSparsePoint, NotDensePoint)
{
    if(!exact)
        return 0;

    if(another == 0 || std::type_index(typeid(*another)) != std::type_index(typeid(DensePoint)))
        throw NotDensePoint();

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
        throw BadIndex("Dimension was skipped while inserting values into DensPoint.");
    if(key >= dimensions)
        throw BadIndex("Given key to insert coordinate value exceeds DensePoint:dimensions.");
    if(this->vector->size() < dimensions)
        this->vector->push_back(value);
    else if(key < this->vector->size())
        (*this->vector)[key] = value;
    else
        throw BadIndex("This is not supported way of inserting a value for given index.");
}

const QList<unsigned> DensePoint::getKeys() const throw(DimensionsNotSet)
{
    if(!initialized)
        throw new DimensionsNotSet("GetKeys can't be called before initilizing all keys!");
    KEYS.wait();
    return *KEYS.get();
}

bool DensePoint::contains(unsigned pid) const throw()
{
    return this->vector->size() > pid;
}

void DensePoint::InitializeKeys(unsigned numD)
{
    dimensions = numD;
    initialized = true;
    KEYS = std::async(std::launch::async, initKeys);
}

QList<unsigned>* DensePoint::initKeys()
{
    QList<unsigned>* result = new QList<unsigned>();
    for(unsigned i = 0; i < dimensions; ++i)
    {
        result->append(i);
    }

    return result;
}

