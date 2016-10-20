#include "notacenterpicker.h"

NotACenterPicker::NotACenterPicker(const char* file, int line) :
    _data("The class given in template is not a center picker class!", file, line)
{
}

const char *NotACenterPicker::what() const throw()
{
    return this->_data.what();
}
