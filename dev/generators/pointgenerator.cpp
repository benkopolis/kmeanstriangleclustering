#ifndef POINTGENERATOR_CPP
#define POINTGENERATOR_CPP

#include "pointgenerator.h"

template<class T>
PointGenerator<T>::PointGenerator() : current(0)
{
}

template<class T>
T *PointGenerator<T>::operator ()()
{
    T* point = new T(this->current++);
    this->generateData(dynamic_cast<AbstractPoint*>(point));
    return point;
}

#endif // POINTGENERATOR_CPP
