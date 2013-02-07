#ifndef DEFAULTNORMALIZEDFORMATDATAREADER_H
#define DEFAULTNORMALIZEDFORMATDATAREADER_H

#include "models.hpp"
#include "abstractdatareader.h"

class DefaultNormalizedFormatDataReader : public AbstractDataReader
{
public:
    DefaultNormalizedFormatDataReader();

	virtual AbstractPointsSpace* readPointSpaceFromFile(QString fileName, AbstractPointsSpace* container);
};

#endif // DEFAULTNORMALIZEDFORMATDATAREADER_H
