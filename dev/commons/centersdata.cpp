#include "centersdata.h"
#include "generators/emptydensepointgenerator.h"

#include <algorithm>

CentersData::CentersData(unsigned nClusters) :
    _centers(nClusters, 0)
{
    EmptyDensePointGenerator generator;
    std::generate_n(this->_centers.begin(), nClusters, generator);
}

DensePoint *CentersData::operator [](const unsigned &index) throw(BadIndex)
{
    if(index >= this->_centers.size())
        throw BadIndex(__FILE__, __LINE__);

    return this->_centers[index];
}

DensePoint const * CentersData::operator [](const unsigned &index) const throw(BadIndex)
{
    if(index >= this->_centers.size())
        throw BadIndex(__FILE__, __LINE__);

    return this->_centers[index];
}
