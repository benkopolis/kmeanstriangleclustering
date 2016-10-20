#ifndef IOEXCEPTION_H
#define IOEXCEPTION_H

#include "base_exception.h"

class IOException : public std::exception
{
public:
    IOException(const char* file, int line);
    IOException(const char* msg, const char* file, int line);
    virtual ~IOException();

    virtual const char* what() const throw();

private:

    base_exception _data;
};

#endif // IOEXCEPTION_H
