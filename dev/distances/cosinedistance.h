#ifndef COSINEDISTANCE_H
#define COSINEDISTANCE_H

#include "abstractdistance.h"
#include "exceptions/notimplemented.h"

class CosineDistance : public AbstractDistance
{
public:
    CosineDistance();
    virtual ~CosineDistance();

    virtual double distance(const AbstractPoint * const one, const AbstractPoint * const two) const;

private:

    double dotMatrixes(const AbstractPoint * const one, const AbstractPoint * const two) const throw();
};

#endif // COSINEDISTANCE_H
