#include <cstdio>
#include <cstring>
#include <iostream>

#include "base_exception.h"

base_exception::base_exception(const char *message, const char *file, int line)
{
    try
    {
        size_t len = strlen(message) + strlen(file) + 14;
        this->_message = new char [len];
        sprintf(this->_message, "%s (%s at %d line).", message, file, line);
    }
    catch(...)
    {
        this->_message = 0;
        std::cerr << "ERR:" << message << " in file " << file << " at " << line << std::endl;
    }
}

base_exception::~base_exception()
{
    delete [] this->_message;
}

const char *base_exception::what() const throw()
{
    return this->getMessage();
}

const char *base_exception::getMessage() const throw()
{
    if (this->_message == 0)
        return "Uknown exception";
    else
        return this->_message;
}
