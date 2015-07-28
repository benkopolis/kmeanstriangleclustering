#ifndef BADINDEX_H
#define BADINDEX_H

#include <exception>

class BadIndex : public std::exception
{
public:
    BadIndex();
    BadIndex(const char* msg);
    virtual ~BadIndex() throw() {}

    virtual const char* what() const throw();

private:

    const char* message;
};

#endif // BADINDEX_H
