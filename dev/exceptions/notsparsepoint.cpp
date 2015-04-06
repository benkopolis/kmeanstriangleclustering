#include "notsparsepoint.h"

NotSparsePoint::NotSparsePoint()
{
}

const char *NotSparsePoint::what() const throw()
{
    return "At this point excpected an instance of SparsePoint class.";
}
