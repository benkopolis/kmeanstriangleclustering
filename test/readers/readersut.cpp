#include "readersut.h"
#include "commons/densepoint.h"
#include "commons/globals.h"

bool ReadersUTHelper::_initialized = false;

ReadersUTHelper::ReadersUTHelper()
{

}

ReadersUTHelper::~ReadersUTHelper()
{

}

std::istream *ReadersUTHelper::getFullDataStream()
{
    std::string str = "6 3 0\n1 2 1\n1 3 1\n0 1 0\n4 5 7\n5 5 7\n0 1 45\n0 2 48\n";
    std::istringstream* stream = new std::istringstream(str);
    return stream;
}

std::istream *ReadersUTHelper::getNormalizedDataStream()
{
    std::string str = "6 10\n0:1 1:2 2:1\n1:1 2:3 3:1\n1:1 2:1 3:1\n3:4 5:5 7:7\n3:5 4:5 7:7\n2:1 9:45\n3:2 9:48\n";
    std::istringstream* stream = new std::istringstream(str);
    return stream;
}

std::istream *ReadersUTHelper::getEmptyStream()
{
    std::string str = "";
    return new std::istringstream(str);
}

std::istream *ReadersUTHelper::getFullDataInvalidStream()
{
    std::string str = "7 3 0\n1 2 1\n1 3 1\n0 1 0\n4 5 7\n5 5 7\n0 1 45\n0 2 48\n";
    std::istringstream* stream = new std::istringstream(str);
    return stream;
}

std::istream *ReadersUTHelper::getNormalizedDataInvalidStream()
{
    std::string str = "6 10\n0:1 1:2 2:1\n1:1 2:3 3:1\n1:1 2:1 3:1\n3:4 5:5 7:7\n3:5 4:5 7:7\n2:1 9:45\n3:2 19:48\n";
    std::istringstream* stream = new std::istringstream(str);
    return stream;
}

void ReadersUTHelper::initialize()
{
    if (!_initialized)
    {
        Globals::DIMENSIONS = 3;
        DensePoint::InitializeKeys(Globals::DIMENSIONS);
        _initialized = true;
    }
}

//#include "moc_fulldatareaderut.cpp"
//#include "moc_normalizedformatdatareaderut.cpp"
//#include "moc_readersut.cpp"
