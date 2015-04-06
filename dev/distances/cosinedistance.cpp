#include "cosinedistance.h"
#include <vector>

CosineDistance::CosineDistance()
{
}

double CosineDistance::distance(AbstractPoint *one, AbstractPoint *two)
{
    return 1.0 - (dotMatrixes(one, two) / sqrt(dotMatrixes(one, one))
                  * sqrt(dotMatrixes(two, two)));
}

double CosineDistance::dotMatrixes(AbstractPoint *one, AbstractPoint *two) throw()
{
    double result = 0;
    std::vector<unsigned> v = getIntersectedIndexes<std::vector<unsigned> >(one, two);
    for(unsigned i : v)
        result = result + (*one)[i] * (*two)[i];

    return result;
}
