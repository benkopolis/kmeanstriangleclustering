#ifndef DIMENSIONSNOTSET_H
#define DIMENSIONSNOTSET_H

#include <exception>

class DimensionsNotSet : public std::exception
{
public:
    DimensionsNotSet();
    DimensionsNotSet(const char* m);
    virtual ~DimensionsNotSet() throw() {};

    virtual const char* what() const throw();

private:

    const char* message;
};

#endif // DIMENSIONSNOTSET_H
