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

    static unsigned GENERATED_DIMENSIONS;

private:

    unsigned current;
};

#include "pointgenerator.cpp"

#endif // POINTGENERATOR_H
