#include "fulldatareader.h"
#include "spaces/pointsspace.h"
#include "commons/densepoint.h"

FullDataReader::FullDataReader()
{

}

FullDataReader::~FullDataReader()
{

}

AbstractPointsSpace<DensePoint> *FullDataReader::parseFile(QTextStream *in) throw (InvalidFileFormat)
{
    if(in->atEnd())
        return 0;

    PointsSpace<DensePoint> *space = new PointsSpace<DensePoint>();
    PointId pointIndex = 0;
    unsigned numP=0, numD=0;
    *in >> numP >> numD;
    space->setNumberOfDimensions(numD);
    space->setNumberOfPoints(numP);
    Coord c = 0.0;
    while(!in->atEnd())
    {
        QString line = in->readLine();
        QTextStream line_in(&line);
        Point* p = new DensePoint();
        unsigned coordtIndex = 0;
        while(!line_in.atEnd() && coordtIndex < numD)
        {
            line_in >> c;
            p->insert(coordtIndex++, c);
        }
        if(coordtIndex != numD) throw new InvalidFileFormat();
        space->insertPoint(p, pointIndex);
        ++pointIndex;
    }
    if(pointIndex != numP) throw new InvalidFileFormat;

    return space;
}
