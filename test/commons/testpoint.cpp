#include "testpoint.h"

TestPoint::TestPoint(unsigned pid, double x, double y):
    AbstractPoint(pid),
    _x(x),
    _y(y)
{
    this->_keys.push_back(0);
    this->_keys.push_back(1);
}

TestPoint::~TestPoint()
{
}

double &TestPoint::operator [](const unsigned &index) throw(BadIndex)
{
    if(index > 1)
        throw (BadIndex(__FILE__, __LINE__));
    return index ? this->_y : this->_x;
}

double TestPoint::operator [](const unsigned &index) const throw(BadIndex)
{
    if(index > 1)
        throw (BadIndex(__FILE__, __LINE__));
    return index ? this->_y : this->_x;
}

void TestPoint::insert(unsigned key, double value) throw(BadIndex)
{
    switch(key)
    {
    case 0:
        this->_x = value;
        break;
    case 1:
        this->_y = value;
        break;
    default:
        throw BadIndex(__FILE__, __LINE__);
    }
}

bool TestPoint::contains(unsigned dimIndex) const throw()
{
    return dimIndex < 2;
}

double TestPoint::get(const unsigned &index) const throw(BadIndex)
{
    if(index > 1)
        throw (BadIndex(__FILE__, __LINE__));
    return index ? this->_y : this->_x;
}

const std::list<unsigned> &TestPoint::getKeys() const throw(DimensionsNotSet)
{
    return this->_keys;
}



