#include "cosinedistance.h"

CosineDistance::CosineDistance()
{
}

double CosineDistance::distance(AbstractPoint *one, AbstractPoint *two)
{
    return 1.0 - (dotMatrixes(p, q) / sqrt(dotMatrixes(p, p))
                  * sqrt(dotMatrixes(q, q)));
}

double CosineDistance::dotMatrixes(AbstractPoint *one, AbstractPoint *two)
{
    throw NotImplemented();
//    double result = 0;
//    for(double c : *one) {
//        for(double i : *two)
//            result = result + c * i;
//    }
//    return result;
}
