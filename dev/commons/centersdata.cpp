#include "centersdata.h"
#include "generators/densepointgenerator.h"

#include <algorithm>

CentersData::CentersData(unsigned nClusters) :
    centers(nClusters, 0)
{
    DensePointGenerator generator;
    std::generate_n(this->centers.begin(), nClusters, generator);
}

DensePoint *CentersData::operator [](const unsigned &index) throw(BadIndex)
{
    if(index >= this->centers.size())
        throw BadIndex(__FILE__, __LINE__);

    return this->centers[index];
}

const DensePoint * const CentersData::operator [](const unsigned &index) const throw(BadIndex)
{
    if(index >= this->centers.size())
        throw BadIndex(__FILE__, __LINE__);

    return this->centers[index];
}
