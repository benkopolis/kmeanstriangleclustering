#ifndef ABSTRACTDATAREADER_H
#define ABSTRACTDATAREADER_H


#include <QString>

#include "models.hpp"
#include "spaces/abstractpointsspace.h"


class AbstractDataReader
{
public:

	virtual AbstractPointsSpace* readPointSpaceFromFile(QString fileName, AbstractPointsSpace* container) = 0;

	virtual ~AbstractDataReader() {}

protected:
    AbstractDataReader();

};

#endif // ABSTRACTDATAREADER_H
