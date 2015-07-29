#ifndef FULLDATAREADER_H
#define FULLDATAREADER_H

#include "abstractdatareader.h"
#include "commons/densepoint.h"

class FullDataReader : public AbstractDataReader<DensePoint>
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
     * <integer:number of points> <integer:number of dimensions> \n(white space separated)
     * <double:coordinate value>{dimensions,dimensions} \n(white space separated)
     */
    virtual AbstractPointsSpace<DensePoint> * parseFile(std::ifstream *in) throw (InvalidFileFormat);

private:

    static FullDataReader _instance;
};

#include "fulldatareader.cpp"

#endif // FULLDATAREADER_H
