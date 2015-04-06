#ifndef NOTIMPLEMENTED_H
#define NOTIMPLEMENTED_H

#include <exception>

class NotImplemented : public std::exception
{
public:
    NotImplemented();

    virtual const char *what() const throw();
};

#endif // NOTIMPLEMENTED_H
