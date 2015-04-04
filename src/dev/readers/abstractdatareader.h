#ifndef ABSTRACTDATAREADER_H
#define ABSTRACTDATAREADER_H


#include <QString>

#include "models.hpp"
#include "spaces/abstractpointsspace.h"

/**
 * @brief The abstract AbstractDataReader class
 */
class AbstractDataReader
{
public:


    /**
     * @brief readPointSpaceFromFile method reads the points' space from the file.
     * @param fileName is the name of the text file with point space in a proper format.
     * @param container - the points' space object.
     * @return The points' space filled with points read from the opened file.
     */
    AbstractPointsSpace* readPointSpaceFromFile(QString fileName);

    virtual AbstractPointsSpace * parseFile(QTextStream *in) = 0;
\
	virtual ~AbstractDataReader() {}

protected:
    AbstractDataReader();

};

#endif // ABSTRACTDATAREADER_H
