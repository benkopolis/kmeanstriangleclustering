#include "centersdata.h"

CentersData::CentersData(unsigned nClusters, unsigned nDims) :
    centers(nClusters, new DensePoint(nDims))
{
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
