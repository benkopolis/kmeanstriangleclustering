#ifndef DENSEPOINTGENERATOR_H
#define DENSEPOINTGENERATOR_H

#include "commons/densepoint.h"
#include "pointgenerator.h"

#include <functional>
#include <random>

class DensePointGenerator : public PointGenerator<DensePoint>
{
public:
    DensePointGenerator();
    ~DensePointGenerator() {}

protected:

    virtual void generateData(AbstractPoint* point) const throw();

private:

    std::function<double()> coords;
    std::uniform_int_distribution<unsigned> dimensionsDistribution;
    std::uniform_real_distribution<double> coordsDistribution;
    std::default_random_engine generator;
};

#endif // DENSEPOINTGENERATOR_H
