#include "spaces/normalizedpointsspace.h"

#ifndef NORMALIZEDFORMATDATAREADER_CPP
#define NORMALIZEDFORMATDATAREADER_CPP

#include "normalizedformatdatareader.h"
#include "commons/sparsepoint.h"

#include <QTextStream>
#include <QFile>

NormalizedFormatDataReader NormalizedFormatDataReader::_instance;

NormalizedFormatDataReader::NormalizedFormatDataReader()
{
}

AbstractPointsSpace<SparsePoint> * NormalizedFormatDataReader::parseFile(QTextStream *in) throw (InvalidFileFormat)
{
    if(in->atEnd())
        return 0;

    PointId pointIndex = 0;
    unsigned int coordtIndex = 0;
    unsigned int numP=0, numD=0;
    *in >> numP >> numD;
    NormalizedPointsSpace<SparsePoint> * space = new NormalizedPointsSpace<SparsePoint>(numP, numD);
    Coord c = 0.0;
    char separator;
    while(!in->atEnd())
    {
        QString line = in->readLine();
        QTextStream line_in(&line);
        SparsePoint* p = new SparsePoint(pointIndex);
        while(!line_in.atEnd())
        {
            line_in >> coordtIndex >> separator >> c;
            if(!p->contains(coordtIndex))
                p->insert(coordtIndex, c);
        }
        space->insertPoint(p, pointIndex);
        ++pointIndex;
    }
    if(pointIndex != numP) throw new InvalidFileFormat;

    return space;
}

#endif //NORMALIZEDFORMATDATAREADER_CPP
