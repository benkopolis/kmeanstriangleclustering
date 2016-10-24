#ifndef NORMALIZEDFORMATDATAREADERUT_H
#define NORMALIZEDFORMATDATAREADERUT_H

#include <UnitTest++/UnitTest++.h>
#include "readers/fulldatareader.h"
#include "readers/normalizedformatdatareader.h"

class ReadersUTHelper
{
public:
    ReadersUTHelper();
    ~ReadersUTHelper();

    std::istream* getFullDataStream();
    std::istream* getNormalizedDataStream();
    std::istream* getEmptyStream();
    std::istream* getFullDataInvalidStream();
    std::istream* getNormalizedDataInvalidStream();

    void initialize();

private:

    static bool _initialized;
};


SUITE(ReadersUT)
{
    TEST(EmptyRead)
    {
        CHECK(true);
    }

    // std::string str = "6 3 0\n1 2 1\n1 3 1\n0 1 0\n4 5 7\n5 5 7\n0 1 45\n0 2 48\n";
    TEST(FullDataReaderOk)
    {
        FullDataReader fdr;
        ReadersUTHelper helper;
        std::istream* stream = helper.getFullDataStream();
        AbstractPointsSpace<DensePoint> * aps = fdr.parseFile(stream);
        delete stream;
        CHECK(aps != NULL);
        CHECK(aps->getNumDimensions() == 3); // in helper string
        CHECK(aps->getNumPoints() == 6); // in helper string
        CHECK(aps->contains(5) == true);
        PtrCAbstractPoint point = (*aps)[5];
        CHECK(point->get(3) == 48);
        delete aps;
    }

    TEST(FullDataReaderEmptyStream)
    {
        FullDataReader fdr;
        ReadersUTHelper helper;
        std::istream* stream = helper.getEmptyStream();
        AbstractPointsSpace<DensePoint> * aps = fdr.parseFile(stream);
        delete stream;
        CHECK(aps == 0);
    }

    TEST(FullDataReaderNullStream)
    {
        FullDataReader fdr;
        AbstractPointsSpace<DensePoint> * aps = fdr.parseFile(0);
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

    //std::string str = "6 10\n0:1 1:2 2:1\n1:1 2:3 3:1\n1:1 2:1 3:1\n3:4 5:5 7:7\n3:5 4:5 7:7\n2:1 9:45\n3:2 9:48\n";
    TEST(SparseDataReaderOk)
    {
        NormalizedFormatDataReader nfdr;
        ReadersUTHelper helper;
        std::istream* stream = helper.getNormalizedDataStream();
        AbstractPointsSpace<SparsePoint> * aps = nfdr.parseFile(stream);
        delete stream;
        CHECK(aps != NULL);
        CHECK(aps->getNumDimensions() == 10); // in helper string
        CHECK(aps->getNumPoints() == 6); // in helper string
        CHECK(aps->contains(5) == true);
        PtrCAbstractPoint point = (*aps)[5];
        CHECK(point->get(9) == 48);
        delete aps;
    }

    TEST(SparseDataReaderEmptyStream)
    {
        NormalizedFormatDataReader nfdr;
        ReadersUTHelper helper;
        std::istream* stream = helper.getEmptyStream();
        AbstractPointsSpace<SparsePoint> * aps = nfdr.parseFile(stream);
        delete stream;
        CHECK(aps == 0);
    }

    TEST(SparseDataReaderNullStream)
    {
        NormalizedFormatDataReader nfdr;
        AbstractPointsSpace<SparsePoint> * aps = nfdr.parseFile(0);
        CHECK(aps == NULL);
    }

    TEST(SparseDataReaderWrongFormat)
    {
        NormalizedFormatDataReader fdr;
        ReadersUTHelper helper;
        std::istream* stream = helper.getFullDataInvalidStream();
        CHECK_THROW(fdr.parseFile(stream), InvalidFileFormat);
    }
}

#endif // NORMALIZEDFORMATDATAREADERUT_H
