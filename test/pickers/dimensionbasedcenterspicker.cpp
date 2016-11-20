#include <UnitTest++/UnitTestPP.h>

#include "commons/sparsepoint.h"
#include "readers/normalizedformatdatareader.h"
#include "pickers/dimensionbasedcenterspicker.h"

SUITE(DimCentersPickerUT)
{
    TEST(EmptyDimBased)
    {
        CHECK(true);
    }

    TEST(SampleDataOkPickDimBased)
    {
        NormalizedFormatDataReader reader;
        AbstractPointsSpace<SparsePoint> * space = reader.readPointSpaceFromFile("sample_data_sparse.txt");
        DimensionBasedCentersPicker<SparsePoint> picker;
        PartitionData *p = picker.performInitialPartition(5, space);
        int pointsNum = 0;
        for(unsigned int i = 0; i<5; ++i)
        {
            pointsNum += p->getPoints(i).size();
        }
        CHECK(pointsNum == space->getDeclaredNumPoints());
        CHECK(pointsNum == space->getNumOfInsertedPoints());
        delete p;
        delete space;
    }
}