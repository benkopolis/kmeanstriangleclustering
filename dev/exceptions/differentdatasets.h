#ifndef DIFFERENTDATASETS_H
#define DIFFERENTDATASETS_H

#include "base_exception.h"

#include <exception>

class DifferentDataSets : public std::exception
{
public:
    DifferentDataSets(char* file, int line);
    DifferentDataSets(char* m, char* file, int line);
    ~DifferentDataSets();

    virtual const char* what() const throw();

private:

    base_exception _data;
};

#endif // DIFFERENTDATASETS_H
