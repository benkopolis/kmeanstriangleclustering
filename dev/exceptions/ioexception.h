#ifndef IOEXCEPTION_H
#define IOEXCEPTION_H

#include <exception>

class IOException : public std::exception
{
public:
    IOException();
    IOException(const char* msg);
    virtual ~IOException();

    virtual const char* what() const throw();

private:

    const char* message;
};

#endif // IOEXCEPTION_H
