#include "differentdatasets.h"

DifferentDataSets::DifferentDataSets(char *file, int line) :
    _data("It is not possible to compare the two given data sets - RAND index", file, line)
{
}

DifferentDataSets::DifferentDataSets(char *m, char *file, int line) :
    _data(m, file, line)
{
}

DifferentDataSets::~DifferentDataSets()
{
}

const char *DifferentDataSets::what() const throw()
{
    return this->_data.what();
}

