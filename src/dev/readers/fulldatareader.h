#ifndef FULLDATAREADER_H
#define FULLDATAREADER_H

#include "abstractdatareader.h"

class FullDataReader : public AbstractDataReader
{
public:
    FullDataReader();
    ~FullDataReader();

    /**
     * @brief readPointSpaceFromFile method reads the points' space from the file.
     * @param in is the input text stream with point space in a proper format.
     * @return The points' space filled with points read from the opened file.
     *
     * The format of the stream is defined as:
     * <integer:number of points> <integer:number of dimensions> \n
     * <double:coordinate value>{dimensions,dimensions} \n
     */
    virtual AbstractPointsSpace * parseFile(QTextStream *in);
};

#endif // FULLDATAREADER_H
