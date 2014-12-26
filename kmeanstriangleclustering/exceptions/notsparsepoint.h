#ifndef NOTSPARSEPOINT_H
#define NOTSPARSEPOINT_H

#include <exception>

class NotSparsePoint : public std::exception
{
public:
    NotSparsePoint();

    virtual const char *what() throw();
};

#endif // NOTSPARSEPOINT_H
