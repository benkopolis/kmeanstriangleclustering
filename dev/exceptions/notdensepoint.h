#ifndef NOTDENSEPOINT_H
#define NOTDENSEPOINT_H

#include "base_exception.h"

class NotDensePoint : public std::exception
{
public:
    NotDensePoint(const char* file, int line);
    ~NotDensePoint();

    virtual const char *what() throw();

private:

    base_exception _data;
};

#endif // NOTDENSEPOINT_H
