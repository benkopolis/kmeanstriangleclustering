#ifndef SEQUENTIALCENTERSPICKER_H
#define SEQUENTIALCENTERSPICKER_H

#include "commons/abstractcenterspicker.h"

class SequentialCentersPicker : public AbstractCentersPicker
{
public:
    SequentialCentersPicker();

    virtual void perform_initial_partition(KMeans* alg);
};

#endif // SEQUENTIALCENTERSPICKER_H
