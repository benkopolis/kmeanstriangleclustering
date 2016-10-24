#ifndef RANDOMCENTERPICKERUT_H
#define RANDOMCENTERPICKERUT_H

#include <UnitTest++/UnitTest++.h>

#include "commons/sparsepoint.h"
#include "readers/normalizedformatdatareader.h"
#include "pickers/randomcenterpicker.h"

SUITE(RandomCentersPickerUT)
{
    TEST(EmptyRead)
    {
        CHECK(true);
    }

    TEST(SampleDataOkPickRandom)
    {
        NormalizedFormatDataReader reader;
        AbstractPointsSpace<SparsePoint> * space = reader.readPointSpaceFromFile("sample_data_sparse.txt");
        RandomCenterPicker picker;
        PartitionData *p = picker.performInitialPartition(5, space);
        int pointsNum = 0;
        for(unsigned int i = 0; i<5; ++i)
        {
            p->getPoints(i)
        }
        delete p;
        delete space;
    }
}

#endif // RANDOMCENTERPICKERUT_H
