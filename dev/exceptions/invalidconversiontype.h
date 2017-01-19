#ifndef INVALIDCONVERSIONTYPE_H
#define INVALIDCONVERSIONTYPE_H

#include "base_exception.h"
#include <exception>

class InvalidConversionType : public std::exception
{
public:
    InvalidConversionType(const char* file, int line);
    InvalidConversionType(const char* m, const char* file, int line);
    virtual ~InvalidConversionType();

    virtual const char* what() const throw();

private:

    base_exception _data;

};

#endif // INVALIDCONVERSIONTYPE_H
