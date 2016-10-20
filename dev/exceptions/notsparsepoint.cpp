#include "notsparsepoint.h"

NotSparsePoint::NotSparsePoint(const char* file, int line) :
    _data("At this point excpected an instance of SparsePoint class.", file, line)
{
}

const char *NotSparsePoint::what() const throw()
{
    return this->_data.what();
}
