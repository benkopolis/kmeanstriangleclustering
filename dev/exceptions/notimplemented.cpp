#include "notimplemented.h"

NotImplemented::NotImplemented(const char* file, int line) :
    _data("This function was not implemented and should not be called.", file, line)
{
}

const char *NotImplemented::what() const throw()
{
    return this->_data.what();
}
