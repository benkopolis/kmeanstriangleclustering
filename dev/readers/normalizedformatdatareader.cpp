#include "spaces/normalizedpointsspace.h"

#ifndef NORMALIZEDFORMATDATAREADER_CPP
#define NORMALIZEDFORMATDATAREADER_CPP

#include "normalizedformatdatareader.h"
#include "commons/sparsepoint.h"

#include <string>
#include <fstream>
#include <iostream>

NormalizedFormatDataReader NormalizedFormatDataReader::_instance;

NormalizedFormatDataReader::NormalizedFormatDataReader()
{
}

AbstractPointsSpace<SparsePoint> * NormalizedFormatDataReader::parseFile(std::ifstream *in) throw (InvalidFileFormat)
{
    if(in->eof() || !in->is_open())
        return 0;

    PointId pointIndex = 0;
    unsigned int coordtIndex = 0;
    unsigned int numP=0, numD=0;
    *in >> numP >> numD;
    NormalizedPointsSpace<SparsePoint> * space = new NormalizedPointsSpace<SparsePoint>(numP, numD);
    Coord c = 0.0;
    char separator;
    while(!in->eof())
    {
        std::string line;
        std::getline(*in, line);
        std::stringstream line_in(std::ios::in);
        line_in.str(line);
        line_in.seekg(0, std::ios::beg);
        SparsePoint* p = new SparsePoint(pointIndex);
        while(!line_in.eof())
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
