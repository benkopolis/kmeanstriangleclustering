#include "sparsepointgenerator.h"
#include "commons/globals.h"

SparsePointGenerator::SparsePointGenerator() :
    dimensionsDistribution(1, Globals::DIMENSIONS),
    coordsDistribution(0.0, 1.0)
{
    this->dimesnions = std::bind(this->dimensionsDistribution, this->generator);
    this->coords = std::bind(this->coordsDistribution, this->generator);
}

void SparsePointGenerator::generateData(AbstractPoint *point) const throw()
{
    for(unsigned totalDims = this->dimesnions(); totalDims > 0; --totalDims) {
        point->insert(this->dimesnions(), this->coords());
    }
}

