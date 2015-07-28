#include "densepointgenerator.h"
#include "commons/globals.h"

DensePointGenerator::DensePointGenerator() :
    coordsDistribution(0.0, 1.0)
{
    this->coords = std::bind(this->coordsDistribution, this->generator);
}

void DensePointGenerator::generateData(AbstractPoint *point) const throw()
{
    for(unsigned d = 0; d < Globals::DIMENSIONS; ++d)
        point->insert(d, this->coords());
}


