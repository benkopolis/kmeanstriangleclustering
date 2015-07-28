#ifndef SPARSEPOINTGENERATOR_H
#define SPARSEPOINTGENERATOR_H

#include "pointgenerator.h"
#include "commons/sparsepoint.h"

#include <functional>
#include <random>

class SparsePointGenerator : public PointGenerator<SparsePoint>
{
public:
    SparsePointGenerator();
    ~SparsePointGenerator() {}

protected:

    virtual void generateData(AbstractPoint* point) const throw();

private:

    std::function<unsigned()> dimesnions;
    std::function<double()> coords;
    std::uniform_int_distribution<unsigned> dimensionsDistribution;
    std::uniform_real_distribution<double> coordsDistribution;
    std::default_random_engine generator;
};

#endif // SPARSEPOINTGENERATOR_H
