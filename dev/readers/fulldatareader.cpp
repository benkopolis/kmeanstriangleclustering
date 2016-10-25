#include "fulldatareader.h"

#ifndef FULLDATAREADER_CPP
#define FULLDATAREADER_CPP

#include "spaces/pointsspace.h"
#include "commons/densepoint.h"

#include <string>
#include <sstream>


FullDataReader FullDataReader::_instance;

FullDataReader::FullDataReader()
{

}

FullDataReader::~FullDataReader()
{

}

AbstractPointsSpace<DensePoint> *FullDataReader::parseFile(std::istream *in) throw (InvalidFileFormat)
{
    if(in == NULL || in->eof() || in->peek() == std::istream::traits_type::eof())
        return 0;

    PointId pointIndex = 0;
    unsigned numP=0, numD=0;
    double quant = 0.0;
    *in >> numP >> numD;
    in->ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    PointsSpace<DensePoint> *space = new PointsSpace<DensePoint>(numP, numD);
    space->setQuant(quant);
    Coord c = 0.0;
    while(!in->eof())
    {
        std::string line;
        std::getline(*in, line);
        if(line.empty())
            continue;
        std::stringstream line_in(std::ios::in);
        line_in.str(line);
        line_in.seekg(0, std::ios_base::beg);
        DensePoint* p = new DensePoint(pointIndex, numD);
        unsigned coordtIndex = 0;
        while(!line_in.eof() && coordtIndex < numD)
        {
            line_in >> c;
            p->insert(coordtIndex++, c);
        }
        if(coordtIndex != numD) throw InvalidFileFormat("Point has wrong number of coordinates", __FILE__, __LINE__);
        space->insertPoint(p, pointIndex);
        ++pointIndex;
    }
    if(pointIndex != numP) throw InvalidFileFormat("Wrong number of points readed", __FILE__, __LINE__);

    return space;
}

#endif //FULLDATAREADER_CPP
