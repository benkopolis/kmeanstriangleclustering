#ifndef INVALIDFILEFORMAT_H
#define INVALIDFILEFORMAT_H

#include <exception>

class InvalidFileFormat : public std::exception
{
public:
    InvalidFileFormat();
    virtual ~InvalidFileFormat();

    virtual const char* what() const throw();
};

#endif // INVALIDFILEFORMAT_H
