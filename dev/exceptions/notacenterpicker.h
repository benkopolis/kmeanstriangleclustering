#ifndef NOTACENTERPICKER_H
#define NOTACENTERPICKER_H

#include <exception>

class NotACenterPicker : public std::exception
{
public:
    NotACenterPicker();

    virtual const char *what() const throw();
};

#endif // NOTACENTERPICKER_H
