#include "ioexception.h"

IOException::IOException() : message("Input output error.")
{

}

IOException::IOException(const char *msg) : message(msg)
{

}

IOException::~IOException()
{

}

const char *IOException::what() const throw()
{
    return this->message;
}

