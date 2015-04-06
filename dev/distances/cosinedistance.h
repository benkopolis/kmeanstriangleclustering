#ifndef COSINEDISTANCE_H
#define COSINEDISTANCE_H

#include "abstractdistance.h"
#include "exceptions/notimplemented.h"

template<typename T>
class CosineDistance : public AbstractDistance
{
public:
    CosineDistance();

    virtual double distance(AbstractPoint *one, AbstractPoint *two);

private:

    double dotMatrixes(AbstractPoint *one, AbstractPoint *two) throw(NotImplemented);
};

#endif // COSINEDISTANCE_H
