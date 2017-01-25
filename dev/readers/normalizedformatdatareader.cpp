#include "spaces/normalizedpointsspace.h"
#include "normalizedformatdatareader.h"
#include "commons/sparsepoint.h"

#include <string>
#include <fstream>
#include <iostream>

NormalizedFormatDataReader::NormalizedFormatDataReader()
{
}

AbstractPointsSpace<SparsePoint> * NormalizedFormatDataReader::parseFile(std::istream *in) throw (InvalidFileFormat)
{
    if(in == NULL || in->eof() || in->peek() == std::istream::traits_type::eof())
        return 0;

    PointId pointIndex = 0;
    unsigned int coordtIndex = 0;
    unsigned int numP=0, numD=0;
    *in >> numP >> numD;
    in->ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    NormalizedPointsSpace<SparsePoint> * space = new NormalizedPointsSpace<SparsePoint>(numP, numD);
    Coord c = 0.0;
    char separator;
    while(!in->eof())
    {
        std::string line;
        std::getline(*in, line);
        if(line.empty())
            continue;
        std::stringstream line_in(std::ios::in);
        line_in.str(line);
        line_in.seekg(0, std::ios::beg);
        SparsePoint* p = new SparsePoint(pointIndex);
        std::string id;
        line_in >> id;
        id = id.substr(0, 1);
        unsigned clusterId = std::strtoul(id.c_str(), nullptr, 0);
        p->setArbitraryClusterId(clusterId);
        while(!line_in.eof())
        {
            line_in >> coordtIndex >> separator >> c;
            if(coordtIndex > numD)
                throw InvalidFileFormat(__FILE__, __LINE__);
            if(!p->contains(coordtIndex))
                p->insert(coordtIndex, c);
        }
        if (p->size() == 0)
            continue;
        space->insertPoint(p, pointIndex);
        ++pointIndex;
    }
    if(pointIndex != numP)
        throw InvalidFileFormat("Wrong number of points read", __FILE__, __LINE__);

    return space;
}
