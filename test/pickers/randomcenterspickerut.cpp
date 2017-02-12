#include <UnitTest++/UnitTestPP.h>

#include "commons/sparsepoint.h"
#include "readers/normalizedformatdatareader.h"
#include "pickers/randomcenterpicker.h"

SUITE(RandomCentersPickerUT)
{
    TEST(EmptyRandPick)
    {
        CHECK(true);
    }

    TEST(SampleDataOkPickRandom)
    {
        NormalizedFormatDataReader reader;
        AbstractPointsSpace * space = reader.readPointSpaceFromFile("sample_data_sparse.txt");
        RandomCenterPicker<SparsePoint> picker;
        PartitionData *p = picker.performInitialPartition(5, space);
        unsigned pointsNum = 0;
        for(unsigned int i = 0; i<5; ++i)
        {
            pointsNum += unsigned(p->getPoints(i).size());
        }
        CHECK(pointsNum == space->getDeclaredNumPoints());
        CHECK(pointsNum == space->getNumOfInsertedPoints());
        delete p;
        delete space;
    }
}
