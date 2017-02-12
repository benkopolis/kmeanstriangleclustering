#include "readersut.h"
#include "commons/densepoint.h"
#include "commons/globals.h"
#include "readers/fulldatareader.h"
#include "readers/normalizedformatdatareader.h"

bool ReadersUTHelper::_initialized = false;

ReadersUTHelper::ReadersUTHelper()
{

}

ReadersUTHelper::~ReadersUTHelper()
{

}

std::istream *ReadersUTHelper::getFullDataStream()
{
    std::string str("7 3\n1 2 1\n1 3 1\n0 1 0\n4 5 7\n5 5 7\n0 1 45\n0 2 48\n");
    std::istringstream* stream = new std::istringstream(str);
    stream->seekg(0, std::ios_base::beg);
    return stream;
}

std::istream *ReadersUTHelper::getNormalizedDataStream()
{
    std::string str("7 10\n0:1 1:2 2:1\n1:1 2:3 3:1\n1:1 2:1 3:1\n3:4 5:5 7:7\n3:5 4:5 7:7\n2:1 9:45\n3:2 9:48\n");
    std::istringstream* stream = new std::istringstream(str);
    stream->seekg(0, std::ios_base::beg);
    return stream;
}

std::istream *ReadersUTHelper::getEmptyStream()
{
    std::string str("");
    return new std::istringstream(str);
}

std::istream *ReadersUTHelper::getFullDataInvalidStream()
{
    std::string str("7 3 0\n1 2 1\n1 3 1\n0 1 0\n4 5 7\n5 5 7\n0 1 45\n0 48\n");
    std::istringstream* stream = new std::istringstream(str);
    stream->seekg(0, std::ios_base::beg);
    return stream;
}

std::istream *ReadersUTHelper::getNormalizedDataInvalidStream()
{
    std::string str("6 10\n0:1 1:2 2:1\n1:1 2:3 3:1\n1:1 2:1 3:1\n3:4 5:5 7:7\n3:5 4:5 7:7\n2:1 9:45\n3:2 19:48\n");
    std::istringstream* stream = new std::istringstream(str);
    stream->seekg(0, std::ios_base::beg);
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


SUITE(ReadersUT)
{
    TEST(EmptyRead)
    {
        CHECK(true);
    }

    // std::string str = "7 3\n1 2 1\n1 3 1\n0 1 0\n4 5 7\n5 5 7\n0 1 45\n0 2 48\n";
    TEST(FullDataReaderOk)
    {
        FullDataReader fdr;
        ReadersUTHelper helper;
        std::istream* stream = helper.getFullDataStream();
        AbstractPointsSpace * aps = fdr.parseFile(stream);
        delete stream;
        CHECK(aps != NULL);
        CHECK(aps->getNumDimensions() == 3); // in helper string
        CHECK(aps->getDeclaredNumPoints() == 7); // in helper string
        CHECK(aps->getDeclaredNumPoints() == aps->getNumOfInsertedPoints());
        CHECK(aps->contains(5) == true);
        PtrCAbstractPoint point = (*aps)[5];
        CHECK(1 == point->get(1));
        delete aps;
    }

    TEST(FullDataReaderEmptyStream)
    {
        FullDataReader fdr;
        ReadersUTHelper helper;
        std::istream* stream = helper.getEmptyStream();
        AbstractPointsSpace * aps = fdr.parseFile(stream);
        delete stream;
        CHECK(aps == 0);
    }

    TEST(FullDataReaderNullStream)
    {
        FullDataReader fdr;
        AbstractPointsSpace * aps = fdr.parseFile(0);
        CHECK(aps == 0);
    }

    TEST(FullDataReaderWrongFormat)
    {
        FullDataReader fdr;
        ReadersUTHelper helper;
        std::istream* stream = helper.getFullDataInvalidStream();
        CHECK_THROW(fdr.parseFile(stream), InvalidFileFormat);
        delete stream;
    }

    //std::string str = "7 10\n0:1 1:2 2:1\n1:1 2:3 3:1\n1:1 2:1 3:1\n3:4 5:5 7:7\n3:5 4:5 7:7\n2:1 9:45\n3:2 9:48\n";
    TEST(SparseDataReaderOk)
    {
        NormalizedFormatDataReader nfdr;
        ReadersUTHelper helper;
        std::istream* stream = helper.getNormalizedDataStream();
        AbstractPointsSpace * aps = nfdr.parseFile(stream);
        delete stream;
        CHECK(aps != NULL);
        CHECK(aps->getNumDimensions() == 10); // in helper string
        CHECK(aps->getDeclaredNumPoints() == 7); // in helper string
        CHECK(aps->getDeclaredNumPoints() == aps->getNumOfInsertedPoints());
        CHECK(aps->contains(5) == true);
        PtrCAbstractPoint point = (*aps)[5];
        CHECK_CLOSE(45, point->get(9), 0.00000001);
        delete aps;
    }

    TEST(SparseDataReaderEmptyStream)
    {
        NormalizedFormatDataReader nfdr;
        ReadersUTHelper helper;
        std::istream* stream = helper.getEmptyStream();
        AbstractPointsSpace * aps = nfdr.parseFile(stream);
        delete stream;
        CHECK(aps == 0);
    }

    TEST(SparseDataReaderNullStream)
    {
        NormalizedFormatDataReader nfdr;
        AbstractPointsSpace * aps = nfdr.parseFile(0);
        CHECK(aps == NULL);
    }

    TEST(SparseDataReaderWrongFormat)
    {
        NormalizedFormatDataReader fdr;
        ReadersUTHelper helper;
        std::istream* stream = helper.getNormalizedDataInvalidStream();
        CHECK_THROW(fdr.parseFile(stream), InvalidFileFormat);
        delete stream;
    }
}

//#include "moc_fulldatareaderut.cpp"
//#include "moc_normalizedformatdatareaderut.cpp"
//#include "moc_readersut.cpp"
