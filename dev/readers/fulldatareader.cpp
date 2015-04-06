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

    PointId pointIndex = 0;
    unsigned numP=0, numD=0;
    *in >> numP >> numD;
    PointsSpace<DensePoint> *space = new PointsSpace<DensePoint>(numP, numD);
    Coord c = 0.0;
    while(!in->atEnd())
    {
        QString line = in->readLine();
        QTextStream line_in(&line);
        DensePoint* p = new DensePoint(pointIndex, numD);
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
