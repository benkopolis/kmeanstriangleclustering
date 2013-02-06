#ifndef ABSTRACTDATAREADER_H
#define ABSTRACTDATAREADER_H


#include "KMeans.hpp"
#include <QString>

class AbstractDataReader
{
public:

	virtual PointsSpace* readPointSpaceFromFile(QString fileName) = 0;

	virtual ~AbstractDataReader() {}

protected:
    AbstractDataReader();

};

#endif // ABSTRACTDATAREADER_H
