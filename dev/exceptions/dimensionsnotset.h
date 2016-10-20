#ifndef DIMENSIONSNOTSET_H
#define DIMENSIONSNOTSET_H

#include "base_exception.h"

class DimensionsNotSet : public std::exception
{
public:
    DimensionsNotSet(const char* file, int line);
    DimensionsNotSet(const char* m, const char* file, int line);
    virtual ~DimensionsNotSet();

    virtual const char* what() const throw();

private:

    base_exception _data;

};

#endif // DIMENSIONSNOTSET_H
