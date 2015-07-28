#ifndef POINTGENERATOR_H
#define POINTGENERATOR_H

#include "commons/abstractpoint.h"
#include "commons/utils.h"

template<class T>
class PointGenerator : private Utils::Where<T, AbstractPoint>
{
public:
    PointGenerator();

    T* operator ()();

protected:

    virtual void generateData(AbstractPoint* point) const throw() = 0;

private:

    unsigned current;
};

#include "pointgenerator.cpp"

#endif // POINTGENERATOR_H
