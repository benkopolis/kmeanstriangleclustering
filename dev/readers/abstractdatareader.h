#ifndef ABSTRACTDATAREADER_H
#define ABSTRACTDATAREADER_H


#include <QString>

#include "models.hpp"
#include "spaces/abstractpointsspace.h"
#include "exceptions/invalidfileformat.h"

/**
 * @brief The abstract AbstractDataReader class
 */
template<typename T>
class AbstractDataReader : private Utils::Where<T, AbstractPoint>
{
public:


    /**
     * @brief readPointSpaceFromFile method reads the points' space from the file.
     * @param fileName is the name of the text file with point space in a proper format.
     * @param container - the points' space object.
     * @return The points' space filled with points read from the opened file.
     */
    AbstractPointsSpace<T> * readPointSpaceFromFile(QString fileName);

    virtual AbstractPointsSpace<T> * parseFile(QTextStream *in) throw (InvalidFileFormat) = 0;
\
	virtual ~AbstractDataReader() {}

protected:
    AbstractDataReader();

};

#endif // ABSTRACTDATAREADER_H