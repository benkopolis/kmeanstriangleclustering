#ifndef NOTSPARSEPOINT_H
#define NOTSPARSEPOINT_H

#include "base_exception.h"

class NotSparsePoint : public std::exception
{
public:
    NotSparsePoint(const char* file, int line);

    virtual const char *what() const throw();

private:

    base_exception _data;
};

#endif // NOTSPARSEPOINT_H
