#include "centersdata.h"
#include "generators/pointgenerator.h"

#include <algorithm>

CentersData::CentersData(unsigned nClusters, unsigned nDims) :
    centers(nClusters, 0)
{
    PointGenerator<DensePoint>::GENERATED_DIMENSIONS = nDims;
    PointGenerator<DensePoint> generator;
    std::generate_n(this->centers.begin(), nClusters, generator);
}

DensePoint *CentersData::operator [](const unsigned &index) throw(BadIndex)
{
    if(index >= this->centers.size())
        throw BadIndex();

    return this->centers[index];
}

const DensePoint * const CentersData::operator [](const unsigned &index) const throw(BadIndex)
{
    if(index >= this->centers.size())
        throw BadIndex();

    return this->centers[index];
}
