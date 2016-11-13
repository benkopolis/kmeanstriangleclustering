#include "emptydensepointgenerator.h"
#include "commons/globals.h"

EmptyDensePointGenerator::EmptyDensePointGenerator()
{
}

void EmptyDensePointGenerator::generateData(AbstractPoint *point) const throw()
{
    for(unsigned d = 0; d < Globals::DIMENSIONS; ++d)
        point->insert(d, 0);
}

