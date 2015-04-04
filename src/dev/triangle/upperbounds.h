#ifndef UPPERBOUNDS_H
#define UPPERBOUNDS_H

#include "abstractaccountingcontainer.h"

class UpperBounds : public AbstractAccountingContainer
{
public:
    UpperBounds(PointsToClusters* pointsToClusters);

    virtual void update(const QVector<Distance>& delta);

private:

    QVector<Distance> upperBounds;
    PointsToClusters* pointsToClusters;
};

#endif // UPPERBOUNDS_H
