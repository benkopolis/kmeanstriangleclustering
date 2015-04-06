#ifndef NOTSPARSEPOINT_H
#define NOTSPARSEPOINT_H

#include <exception>

class NotSparsePoint : public std::exception
{
public:
    NotSparsePoint();

    virtual const char *what() const throw();
};

#endif // NOTSPARSEPOINT_H
