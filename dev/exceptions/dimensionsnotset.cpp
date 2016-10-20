#include "dimensionsnotset.h"

DimensionsNotSet::DimensionsNotSet(const char *file, int line) :
    _data("DensePoint:dimensions was not set before first creation of DensePoint object, or it was set to 0.", file, line)
{
}

DimensionsNotSet::DimensionsNotSet(const char *m, const char *file, int line) :
    _data(m, file, line)
{
}

DimensionsNotSet::~DimensionsNotSet() {}

const char *DimensionsNotSet::what() const throw()
{
    return this->_data.what();
}

