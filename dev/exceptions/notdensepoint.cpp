#include "notdensepoint.h"

NotDensePoint::NotDensePoint()
{

}

NotDensePoint::~NotDensePoint()
{

}

const char *NotDensePoint::what() throw()
{
    return "At this point excpected an instance of DensePoint class.";
}

