#ifndef BASE_EXCEPTION_H
#define BASE_EXCEPTION_H

#include <exception>

class base_exception : std::exception
{
public:
    base_exception(const char* message, const char* file, int line);
    virtual ~base_exception();

    virtual const char* what() const throw();

protected:

    char* _message;

    const char* getMessage() const throw();

    int _bufferSize;
    void** _stackBuffer;
    char** _stackTrace;

};

#endif // BASE_EXCEPTION_H
