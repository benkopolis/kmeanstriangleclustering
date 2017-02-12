#include "variationofinformationindex.h"

#include <cmath>

VariationOfInformationIndex::VariationOfInformationIndex()
{

}

VariationOfInformationIndex::~VariationOfInformationIndex()
{

}

double VariationOfInformationIndex::count(PartitionData *one, PartitionData *two)
{
    double n = one->getNumberOfPoints();
    double total = 0, r, qi, pi;
    for(unsigned i = 0; i < one->getNumberOfClusters(); ++i)
    {
        const std::unordered_set<unsigned> one_points = one->getPoints(i);
        pi = double(one->getPoints(i).size()) / n;
        for(unsigned j = i + 1; j < two->getNumberOfClusters(); ++j)
        {
            const std::unordered_set<unsigned> two_points = one->getPoints(j);
            double ri = 0;
            for(unsigned one_i : one_points)
            {
                if (two_points.count(one_i) > 0)
                    ri += 1.0;
            }
            ri = ri / n;
            qi = double(two->getPoints(j).size()) / n;
            total += ri * (log(ri/pi) + log(ri/qi));
        }
    }

    total = total * (-1);
    return total;
}

