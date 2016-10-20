#ifndef BADINDEX_H
#define BADINDEX_H

#include "base_exception.h"

class BadIndex : public std::exception
{
public:
    BadIndex(const char* file, int line);
    BadIndex(const char* msg, const char* file, int line);
    virtual ~BadIndex() throw() {}

    virtual const char* what() const throw();

private:

    base_exception _data;
};

#endif // BADINDEX_H
