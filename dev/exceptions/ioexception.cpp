#include "ioexception.h"

IOException::IOException(const char* file, int line) :
    _data("Input output error.", file, line)
{

}

IOException::IOException(const char *msg, const char *file, int line) :
    _data(msg, file, line)
{
}

IOException::~IOException()
{
}

const char *IOException::what() const throw()
{
    return this->_data.what();
}

