#ifndef POINTGENERATOR_CPP
#define POINTGENERATOR_CPP

#include "pointgenerator.h"

template<class T>
unsigned PointGenerator<T>::GENERATED_DIMENSIONS = 0;

template<class T>
PointGenerator<T>::PointGenerator() : current(0)
{
}

template<class T>
T *PointGenerator<T>::operator ()()
{
    return new T(this->current++, GENERATED_DIMENSIONS);
}

#endif // POINTGENERATOR_CPP
