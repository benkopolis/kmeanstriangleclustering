#ifndef NOTDENSEPOINT_H
#define NOTDENSEPOINT_H

#include <exception>

class NotDensePoint : public std::exception
{
public:
    NotDensePoint();
    ~NotDensePoint();

    virtual const char *what() throw();
};

#endif // NOTDENSEPOINT_H
