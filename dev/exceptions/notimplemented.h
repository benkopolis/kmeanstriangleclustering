#ifndef NOTIMPLEMENTED_H
#define NOTIMPLEMENTED_H

#include "base_exception.h"

class NotImplemented : public std::exception
{
public:
    NotImplemented(const char* file, int line);

    virtual const char *what() const throw();

private:

    base_exception _data;
};

#endif // NOTIMPLEMENTED_H
