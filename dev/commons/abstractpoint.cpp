#include "abstractpoint.h"

//#ifndef ABSTRACTPOINT_CPP
//#define ABSTRACTPOINT_CPP


//#endif // ABSTRACTPOINT_CPP


AbstractPoint::AbstractPoint(unsigned pid)
 : _pointId(pid),
   _userClusterId(-1)
{

}

AbstractPoint::AbstractPoint(const AbstractPoint &other)
{
    this->_userClusterId = other._userClusterId;
    this->_pointId = other._pointId;
}

AbstractPoint::AbstractPoint(AbstractPoint &&other)
{
    this->_userClusterId = other._userClusterId;
    this->_pointId = other._pointId;
    other._userClusterId = -1;
    other._pointId = -1;
}

AbstractPoint::~AbstractPoint()
{
}

unsigned AbstractPoint::getPointId()
{
    return this->_pointId;
}

unsigned AbstractPoint::getArbitraryClusterId() const throw()
{
    return this->_userClusterId;
}

void AbstractPoint::setArbitraryClusterId(unsigned userClusterId) throw()
{
    this->_userClusterId = userClusterId;
}
