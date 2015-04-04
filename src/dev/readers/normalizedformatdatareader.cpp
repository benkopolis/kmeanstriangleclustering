#include "normalizedformatdatareader.h"


#include <QTextStream>
#include <QFile>

#include "spaces/normalizedpointsspace.h"

NormalizedFormatDataReader::NormalizedFormatDataReader()
{
}

AbstractPointsSpace * NormalizedFormatDataReader::parseFile(QTextStream *in)
{
    if(in->atEnd())
        return 0;

    NormalizedPointsSpace * space = new NormalizedPointsSpace();
    PointId pointIndex = 0;
    unsigned int coordtIndex = 0;
    unsigned int numP=0, numD=0;
    *in >> numP >> numD;
    space->setNumberOfDimensions(numD);
    space->setNumberOfPoints(numP);
    Coord c = 0.0;
    char separator;
    while(!in->atEnd())
    {
        QString line = in->readLine();
        QTextStream line_in(&line);
        Point* p = new Point();
        while(!line_in.atEnd())
        {
            line_in >> coordtIndex >> separator >> c;
            if(!p->contains(coordtIndex))
                p->insert(coordtIndex, c);
        }
        space->insertPoint(p, pointIndex);
        ++pointIndex;
    }

    return space;
}
