#ifndef UPPERBOUNDS_H
#define UPPERBOUNDS_H

#include "abstractaccountingcontainer.h"

#include <unordered_map>
#include <vector>

class UpperBounds : public AbstractAccountingContainer
{
public:
    UpperBounds(std::unordered_map<unsigned, unsigned>* pointsToClusters);

    virtual void update(const QVector<Distance>& delta);

private:

    std::vector<Distance> upperBounds;
    std::unordered_map<unsigned, unsigned>* pointsToClusters;
};

#endif // UPPERBOUNDS_H
