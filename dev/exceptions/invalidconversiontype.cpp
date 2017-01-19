#include "invalidconversiontype.h"


InvalidConversionType::InvalidConversionType(const char *file, int line) :
    _data("Class is convertable, but does not know how to convert itself to the given type", file, line)
{

}

InvalidConversionType::InvalidConversionType(const char *m, const char *file, int line):
    _data(m, file, line)
{

}

InvalidConversionType::~InvalidConversionType()
{
}

const char *InvalidConversionType::what() const throw()
{
    return this->_data.what();
}
