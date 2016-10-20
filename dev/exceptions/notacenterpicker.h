#ifndef NOTACENTERPICKER_H
#define NOTACENTERPICKER_H

#include "base_exception.h"

class NotACenterPicker : public std::exception
{
public:
    NotACenterPicker(const char* file, int line);

    virtual const char *what() const throw();

private:

    base_exception _data;

};

#endif // NOTACENTERPICKER_H
