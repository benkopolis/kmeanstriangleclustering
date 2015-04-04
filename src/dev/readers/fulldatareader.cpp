#include "fulldatareader.h"
#include "spaces/pointsspace.h"

FullDataReader::FullDataReader()
{

}

FullDataReader::~FullDataReader()
{

}

AbstractPointsSpace *FullDataReader::parseFile(QTextStream *in)
{
    if(in->atEnd())
        return 0;

    NormalizedPointsSpace *space = new NormalizedPointsSpace();
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
        Point* p = new Point();
        unsigned coordtIndex = 0;
        while(!line_in.atEnd() && coordtIndex < numD)
        {
            line_in >> c;
            p->insert(coordtIndex++, c);
        }
        space->insertPoint(p, pointIndex);
        ++pointIndex;
    }

    return space;
}
