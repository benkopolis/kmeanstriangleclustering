#ifndef ABSTRACTCENTERSPICKER_H
#define ABSTRACTCENTERSPICKER_H

#include "KMeans.hpp"

class AbstractCentersPicker
{
public:

    virtual void perform_initial_partition(KMeans* alg) = 0;

protected:
    AbstractCentersPicker();
};

#endif // ABSTRACTCENTERSPICKER_H
