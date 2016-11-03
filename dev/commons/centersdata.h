#ifndef CENTERSDATA_H
#define CENTERSDATA_H

#include "densepoint.h"
#include "partitiondata.h"
#include "exceptions/badindex.h"
#include <vector>

class CentersData
{
public:
    CentersData(unsigned nClusters);

    DensePoint *operator [] (const unsigned& index) throw(BadIndex);
    DensePoint const * operator [] (const unsigned& index) const throw(BadIndex);

    std::vector<DensePoint* >::iterator begin() { return this->_centers.begin(); }
    std::vector<DensePoint* >::const_iterator begin() const { return this->_centers.begin(); }
    std::vector<DensePoint* >::iterator end() { return this->_centers.end(); }
    std::vector<DensePoint* >::const_iterator end() const { return this->_centers.end(); }

    unsigned size() const { return this->_centers.size(); }

private:

    std::vector<DensePoint* > _centers;
};

#endif // CENTERSDATA_H
