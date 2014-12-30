#ifndef BADINDEX_H
#define BADINDEX_H

#include <exception>

class BadIndex : public std::exception
{
public:
    BadIndex();
    virtual ~BadIndex() throw();

    virtual const char* what() const throw();
};

#endif // BADINDEX_H
