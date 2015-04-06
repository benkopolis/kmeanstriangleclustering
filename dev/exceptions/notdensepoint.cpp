#include "notdensepoint.h"

NotDensePoint::NotDensePoint()
{

}

NotDensePoint::~NotDensePoint()
{

}

const char *NotDensePoint::what()
{
    return "At this point excpected an instance of DensePoint class.";
}

