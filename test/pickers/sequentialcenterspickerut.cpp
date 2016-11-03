#include <UnitTest++/UnitTestPP.h>
#include "pickers/sequentialcenterspicker.h"
#include "readers/normalizedformatdatareader.h"

SUITE(SequentialCentersPickerUT)
{
    TEST(EmptySeqPick)
    {
        CHECK(true);
    }

    TEST(SampleDataOkPickSeq)
    {
        NormalizedFormatDataReader reader;
        AbstractPointsSpace<SparsePoint> * space = reader.readPointSpaceFromFile("sample_data_sparse.txt");
        SequentialCentersPicker<SparsePoint> picker;
        PartitionData *p = picker.performInitialPartition(5, space);
        int pointsNum = 0;
        for(unsigned int i = 0; i<5; ++i)
        {
            pointsNum += p->getPoints(i).size();
            CHECK(p->getPoints(i).size() == 5);
        }
        CHECK(pointsNum == space->getDeclaredNumPoints());
        CHECK(pointsNum == space->getNumOfInsertedPoints());
        delete p;
        delete space;
    }
}
