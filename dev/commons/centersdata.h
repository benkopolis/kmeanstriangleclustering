#ifndef CENTERSDATA_H
#define CENTERSDATA_H

#include "densepoint.h"
#include "partitiondata.h"
#include "exceptions/badindex.h"
#include <vector>

class CentersData
{
public:
    CentersData(unsigned nClusters, unsigned nDims);

    static CentersData* countCenters(PartitionData* data);

    DensePoint *operator [] (const unsigned& index) throw(BadIndex);
    DensePoint const * const operator [] (const unsigned& index) const throw(BadIndex);


private:

    std::vector<DensePoint* > centers;
};

#endif // CENTERSDATA_H
