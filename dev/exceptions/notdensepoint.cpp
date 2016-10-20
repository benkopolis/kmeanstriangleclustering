#include "notdensepoint.h"

NotDensePoint::NotDensePoint(const char* file, int line) :
    _data("At this point excpected an instance of DensePoint class.", file, line)
{
}

NotDensePoint::~NotDensePoint()
{
}

const char *NotDensePoint::what() throw()
{
    return this->_data.what();
}

