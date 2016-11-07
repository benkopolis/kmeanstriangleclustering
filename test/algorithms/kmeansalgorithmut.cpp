#include <UnitTest++/UnitTestPP.h>

#define PERFORMANCE_TEST

#include "algorithms/kmeansalgorithm.h"
#include "commons/sparsepoint.h"
#include "pickers/randomcenterpicker.h"
#include "pickers/sequentialcenterspicker.h"
#include "commons/partitiondata.h"
#include "commons/centersdata.h"
#include "spaces/normalizedpointsspace.h"
#include "distances/cosinedistance.h"
#include "distances/euclideandistance.h"
#include "distances/hamiltondistance.h"
#include "distances/manhattandistance.h"
#include "readers/normalizedformatdatareader.h"

SUITE(KMeansTests)
{
    TEST(KMeansEmpty)
    {
    }

    TEST(KMeansCorrectDataRandomPickerCosineDist)
    {
        CosineDistance* distance = new CosineDistance();
        RandomCenterPicker<SparsePoint>* picker = new RandomCenterPicker<SparsePoint>();
        NormalizedFormatDataReader reader;
        AbstractPointsSpace<SparsePoint> * space = reader.readPointSpaceFromFile("sample_data_sparse.txt");
        KMeansAlgorithm<SparsePoint,CosineDistance> * algo =
                new KMeansAlgorithm<SparsePoint, CosineDistance>(distance, picker, space, 5, 10);
        algo->execute();
        CHECK(algo->getCentersData() != NULL);
        CHECK(algo->getPartitionData() != NULL);
        delete distance;
        delete picker;
        delete space;
        delete algo;
    }
}
