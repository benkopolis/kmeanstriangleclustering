#ifndef COSINEDISTANCE_H
#define COSINEDISTANCE_H

#include "abstractdistance.h"
#include "exceptions/notimplemented.h"

class CosineDistance : public AbstractDistance
{
public:
    CosineDistance();

    virtual double distance(AbstractPoint *one, AbstractPoint *two) const;

private:

    double dotMatrixes(AbstractPoint *one, AbstractPoint *two) const throw();
};

#endif // COSINEDISTANCE_H
