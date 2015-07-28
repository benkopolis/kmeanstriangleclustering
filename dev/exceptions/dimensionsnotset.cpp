#include "dimensionsnotset.h"

DimensionsNotSet::DimensionsNotSet() :
    message("DensePoint:dimensions was not set before first creation of DensePoint object, or it was set to 0.")
{
}

DimensionsNotSet::DimensionsNotSet(const char *m) :
    message(m)
{
}

const char *DimensionsNotSet::what() const throw()
{
    return this->message;
}

