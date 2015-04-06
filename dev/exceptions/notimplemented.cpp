#include "notimplemented.h"

NotImplemented::NotImplemented()
{
}

const char *NotImplemented::what() const throw()
{
    return "This function was not implemented and should not be called.";
}
