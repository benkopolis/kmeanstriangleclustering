#ifndef INVALIDFILEFORMAT_H
#define INVALIDFILEFORMAT_H

#include "base_exception.h"

class InvalidFileFormat : public std::exception
{
public:
    InvalidFileFormat(const char* file, int line);
    virtual ~InvalidFileFormat();

    virtual const char* what() const throw();

private:

    base_exception _data;
};

#endif // INVALIDFILEFORMAT_H
