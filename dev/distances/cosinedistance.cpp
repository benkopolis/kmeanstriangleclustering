#include "cosinedistance.h"
#include <vector>

CosineDistance::CosineDistance()
{
}

CosineDistance::~CosineDistance()
{
}

double CosineDistance::distance(const AbstractPoint * const one, const AbstractPoint * const two) const
{
    double top = dotMatrixes(one, two);
    double bottom_left = sqrt(dotMatrixes(one, one));
    double bottom_right = sqrt(dotMatrixes(two, two));
    double bottom = bottom_left * bottom_right;
    double similarity = top / bottom;
    return 1.0 - similarity;
}

double CosineDistance::dotMatrixes(const AbstractPoint * const one, const AbstractPoint * const two) const throw()
{
    double result = 0;
    std::vector<unsigned> v = getIntersectedIndexes<std::vector<unsigned> >(one, two);
    for(unsigned i : v)
        result = result + (*one)[i] * (*two)[i];

    return result;
}
