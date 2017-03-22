#include "variationofinformationindex.h"

#include <cmath>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <memory>
#include <list>

void print_set(const std::unordered_set<unsigned>& set)
{
    std::cerr << "[ ";
    std::copy(
            set.begin(),
            set.end(),
            std::ostream_iterator<unsigned>(std::cerr, ", ")
            );
    std::cerr << " ]" << std::endl;
}

VariationOfInformationIndex::VariationOfInformationIndex()
{

}

VariationOfInformationIndex::~VariationOfInformationIndex()
{

}

double VariationOfInformationIndex::count(const PartitionData *one, const PartitionData *two)
{
    double n = one->getNumberOfPoints() + two->getNumberOfPoints();
    double total = 0, qi = 0, pi = 0;
    for(unsigned i = 0; i < one->getNumberOfClusters(); ++i)
    {
        const std::unordered_set<unsigned> one_points = one->getPoints(i);
        pi = double(one->getPoints(i).size()) / n;
        for(unsigned j = 0; j < two->getNumberOfClusters(); ++j)
        {
            const std::unordered_set<unsigned> two_points = two->getPoints(j);
//            std::cerr << "ONE " << i << " ";
//            print_set(one_points);
//            std::cerr << "TWO " << j << " ";
//            print_set(two_points);
            std::list<unsigned> intersection;
            std::set_intersection(
                        one_points.begin(),
                        one_points.end(),
                        two_points.begin(),
                        two_points.end(),
                        std::inserter(
                            intersection,
                            intersection.begin()));
            double ri = double(intersection.size()) / n;
//            std::cerr << "INTER = " << intersection.size() << std::endl;
//            std::cerr << "pi = " << pi << " qi = " << qi << std::endl;
//            std::cerr << "ri = " << ri << std::endl;
            qi = double(two->getPoints(j).size()) / n;
            if (ri > 0)
            {
//                std::cerr << "pi = " << pi << " qi = " << qi << std::endl;
                std::cerr << "(ri * (log(ri/pi) + log(ri/qi))) = " << (ri * (log(ri/pi) + log(ri/qi))) << std::endl;
                total = total + (ri * (log2(ri/pi) + log2(ri/qi)));
            }
        }
    }

    total = fabs(total) / log2(n);
    return total;
}

