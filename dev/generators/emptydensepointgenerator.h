#ifndef EMPTYDENSEPOINTGENERATOR_H
#define EMPTYDENSEPOINTGENERATOR_H

#include "pointgenerator.h"
#include "commons/densepoint.h"

class EmptyDensePointGenerator : public PointGenerator<DensePoint>
{
public:
    EmptyDensePointGenerator();

protected:

    virtual void generateData(AbstractPoint* point) const throw();
};

#endif // EMPTYDENSEPOINTGENERATOR_H
