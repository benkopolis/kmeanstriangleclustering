#ifndef DEFAULTNORMALIZEDFORMATDATAREADER_H
#define DEFAULTNORMALIZEDFORMATDATAREADER_H

#include "models.hpp"
#include "abstractdatareader.h"

class NormalizedFormatDataReader : public AbstractDataReader
{
public:
    NormalizedFormatDataReader();

    /**
     * @brief readPointSpaceFromFile Reads the points' space from the file.
     * @param in is text stream with a point space in a proper format.
     * @return The points' space filled with points read from the opened file.
     *
     * The format of the file is defined as:
     * <integer:number of points> <integer:number of dimensions> \n
     * <integer:dimension ordinate number>:<double:coordinate value>{1,dimensions} \n
     */
    AbstractPointsSpace *parseFile(QTextStream *in);
};

#endif // DEFAULTNORMALIZEDFORMATDATAREADER_H
