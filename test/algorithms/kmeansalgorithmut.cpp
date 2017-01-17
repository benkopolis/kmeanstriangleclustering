#include <UnitTest++/UnitTestPP.h>
#include <iostream>

//#define PERFORMANCE_TEST
//#define DIAGNOSTICS_DEBUG

#include "algorithms/kmeansalgorithm.h"
#include "commons/sparsepoint.h"
#include "pickers/randomcenterpicker.h"
#include "pickers/sequentialcenterspicker.h"
#include "pickers/dimensionbasedcenterspicker.h"
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
        KMeansAlgorithm<SparsePoint> * algo =
                new KMeansAlgorithm<SparsePoint>(distance, picker, space, 5, 5);
        algo->execute();
        CHECK(algo->getCentersData() != NULL);
        CHECK(algo->getPartitionData() != NULL);
        std::cerr << "KMeansCorrectDataRandomPickerCosineDist " << algo->getNumberOfIterations() << std::endl;
        delete distance;
        delete picker;
        delete space;
        delete algo;
    }

    TEST(KMeansCorrectDataRandomPickerEuclideanDist)
    {
        EuclideanDistance* distance = new EuclideanDistance();
        RandomCenterPicker<SparsePoint>* picker = new RandomCenterPicker<SparsePoint>();
        NormalizedFormatDataReader reader;
        AbstractPointsSpace<SparsePoint> * space = reader.readPointSpaceFromFile("sample_data_sparse.txt");
        KMeansAlgorithm<SparsePoint> * algo =
                new KMeansAlgorithm<SparsePoint>(distance, picker, space, 5, 5);
        algo->execute();
        CHECK(algo->getCentersData() != NULL);
        CHECK(algo->getPartitionData() != NULL);
        std::cerr << "KMeansCorrectDataRandomPickerEuclideanDist " << algo->getNumberOfIterations() << std::endl;
        delete distance;
        delete picker;
        delete space;
        delete algo;
    }

    TEST(KMeansCorrectDataRandomPickerHamiltonDist)
    {
        HamiltonDistance* distance = new HamiltonDistance();
        RandomCenterPicker<SparsePoint>* picker = new RandomCenterPicker<SparsePoint>();
        NormalizedFormatDataReader reader;
        AbstractPointsSpace<SparsePoint> * space = reader.readPointSpaceFromFile("sample_data_sparse.txt");
        KMeansAlgorithm<SparsePoint> * algo =
                new KMeansAlgorithm<SparsePoint>(distance, picker, space, 5, 5);
        algo->execute();
        CHECK(algo->getCentersData() != NULL);
        CHECK(algo->getPartitionData() != NULL);
        std::cerr << "KMeansCorrectDataRandomPickerHamiltonDist " << algo->getNumberOfIterations() << std::endl;
        delete distance;
        delete picker;
        delete space;
        delete algo;
    }

    TEST(KMeansCorrectDataRandomPickerManhattanDist)
    {
        ManhattanDistance* distance = new ManhattanDistance();
        RandomCenterPicker<SparsePoint>* picker = new RandomCenterPicker<SparsePoint>();
        NormalizedFormatDataReader reader;
        AbstractPointsSpace<SparsePoint> * space = reader.readPointSpaceFromFile("sample_data_sparse.txt");
        KMeansAlgorithm<SparsePoint> * algo =
                new KMeansAlgorithm<SparsePoint>(distance, picker, space, 5, 5);
        algo->execute();
        CHECK(algo->getCentersData() != NULL);
        CHECK(algo->getPartitionData() != NULL);
        std::cerr << "KMeansCorrectDataRandomPickerManhattanDist " << algo->getNumberOfIterations() << std::endl;
        delete distance;
        delete picker;
        delete space;
        delete algo;
    }

    TEST(KMeansCorrectDataSeqPickerCosineDist)
    {
        CosineDistance* distance = new CosineDistance();
        SequentialCentersPicker<SparsePoint>* picker = new SequentialCentersPicker<SparsePoint>();
        NormalizedFormatDataReader reader;
        AbstractPointsSpace<SparsePoint> * space = reader.readPointSpaceFromFile("sample_data_sparse.txt");
        KMeansAlgorithm<SparsePoint> * algo =
                new KMeansAlgorithm<SparsePoint>(distance, picker, space, 5, 5);
        algo->execute();
        CHECK(algo->getCentersData() != NULL);
        CHECK(algo->getPartitionData() != NULL);
        std::cerr << "KMeansCorrectDataRandomPickerCosineDist " << algo->getNumberOfIterations() << std::endl;
        delete distance;
        delete picker;
        delete space;
        delete algo;
    }

    TEST(KMeansCorrectDataSeqPickerEuclideanDist)
    {
        EuclideanDistance* distance = new EuclideanDistance();
        SequentialCentersPicker<SparsePoint>* picker = new SequentialCentersPicker<SparsePoint>();
        NormalizedFormatDataReader reader;
        AbstractPointsSpace<SparsePoint> * space = reader.readPointSpaceFromFile("sample_data_sparse.txt");
        KMeansAlgorithm<SparsePoint> * algo =
                new KMeansAlgorithm<SparsePoint>(distance, picker, space, 5, 5);
        algo->execute();
        CHECK(algo->getCentersData() != NULL);
        CHECK(algo->getPartitionData() != NULL);
        std::cerr << "KMeansCorrectDataRandomPickerEuclideanDist " << algo->getNumberOfIterations() << std::endl;
        delete distance;
        delete picker;
        delete space;
        delete algo;
    }

    TEST(KMeansCorrectDataSeqPickerHamiltonDist)
    {
        HamiltonDistance* distance = new HamiltonDistance();
        SequentialCentersPicker<SparsePoint>* picker = new SequentialCentersPicker<SparsePoint>();
        NormalizedFormatDataReader reader;
        AbstractPointsSpace<SparsePoint> * space = reader.readPointSpaceFromFile("sample_data_sparse.txt");
        KMeansAlgorithm<SparsePoint> * algo =
                new KMeansAlgorithm<SparsePoint>(distance, picker, space, 5, 5);
        algo->execute();
        CHECK(algo->getCentersData() != NULL);
        CHECK(algo->getPartitionData() != NULL);
        std::cerr << "KMeansCorrectDataRandomPickerHamiltonDist " << algo->getNumberOfIterations() << std::endl;
        delete distance;
        delete picker;
        delete space;
        delete algo;
    }

    TEST(KMeansCorrectDataSeqPickerManhattanDist)
    {
        ManhattanDistance* distance = new ManhattanDistance();
        SequentialCentersPicker<SparsePoint>* picker = new SequentialCentersPicker<SparsePoint>();
        NormalizedFormatDataReader reader;
        AbstractPointsSpace<SparsePoint> * space = reader.readPointSpaceFromFile("sample_data_sparse.txt");
        KMeansAlgorithm<SparsePoint> * algo =
                new KMeansAlgorithm<SparsePoint>(distance, picker, space, 5, 5);
        algo->execute();
        CHECK(algo->getCentersData() != NULL);
        CHECK(algo->getPartitionData() != NULL);
        std::cerr << "KMeansCorrectDataRandomPickerManhattanDist " << algo->getNumberOfIterations() << std::endl;
        delete distance;
        delete picker;
        delete space;
        delete algo;
    }

    TEST(KMeansCorrectDataDimPickerCosineDist)
    {
        CosineDistance* distance = new CosineDistance();
        DimensionBasedCentersPicker<SparsePoint>* picker = new DimensionBasedCentersPicker<SparsePoint>();
        NormalizedFormatDataReader reader;
        AbstractPointsSpace<SparsePoint> * space = reader.readPointSpaceFromFile("sample_data_sparse.txt");
        KMeansAlgorithm<SparsePoint> * algo =
                new KMeansAlgorithm<SparsePoint>(distance, picker, space, 5, 5);
        algo->execute();
        CHECK(algo->getCentersData() != NULL);
        CHECK(algo->getPartitionData() != NULL);
        std::cerr << "KMeansCorrectDataRandomPickerCosineDist " << algo->getNumberOfIterations() << std::endl;
        delete distance;
        delete picker;
        delete space;
        delete algo;
    }

    TEST(KMeansCorrectDataDimPickerEuclideanDist)
    {   // give proper clustering results,
        EuclideanDistance* distance = new EuclideanDistance();
        DimensionBasedCentersPicker<SparsePoint>* picker = new DimensionBasedCentersPicker<SparsePoint>();
        NormalizedFormatDataReader reader;
        AbstractPointsSpace<SparsePoint> * space = reader.readPointSpaceFromFile("sample_data_sparse.txt");
        KMeansAlgorithm<SparsePoint> * algo =
                new KMeansAlgorithm<SparsePoint>(distance, picker, space, 5, 5);
        algo->execute();
        CHECK(algo->getCentersData() != NULL);
        CHECK(algo->getPartitionData() != NULL);
        std::cerr << "KMeansCorrectDataRandomPickerEuclideanDist " << algo->getNumberOfIterations() << std::endl;
        delete distance;
        delete picker;
        delete space;
        delete algo;
    }

    TEST(KMeansCorrectDataDimPickerHamiltonDist)
    {
        HamiltonDistance* distance = new HamiltonDistance();
        DimensionBasedCentersPicker<SparsePoint>* picker = new DimensionBasedCentersPicker<SparsePoint>();
        NormalizedFormatDataReader reader;
        AbstractPointsSpace<SparsePoint> * space = reader.readPointSpaceFromFile("sample_data_sparse.txt");
        KMeansAlgorithm<SparsePoint> * algo =
                new KMeansAlgorithm<SparsePoint>(distance, picker, space, 5, 5);
        algo->execute();
        CHECK(algo->getCentersData() != NULL);
        CHECK(algo->getPartitionData() != NULL);
        std::cerr << "KMeansCorrectDataRandomPickerHamiltonDist " << algo->getNumberOfIterations() << std::endl;
        delete distance;
        delete picker;
        delete space;
        delete algo;
    }

    TEST(KMeansCorrectDataDimPickerManhattanDist)
    {
        ManhattanDistance* distance = new ManhattanDistance();
        DimensionBasedCentersPicker<SparsePoint>* picker = new DimensionBasedCentersPicker<SparsePoint>();
        NormalizedFormatDataReader reader;
        AbstractPointsSpace<SparsePoint> * space = reader.readPointSpaceFromFile("sample_data_sparse.txt");
        KMeansAlgorithm<SparsePoint> * algo =
                new KMeansAlgorithm<SparsePoint>(distance, picker, space, 5, 5);
        algo->execute();
        CHECK(algo->getCentersData() != NULL);
        CHECK(algo->getPartitionData() != NULL);
        std::cerr << "KMeansCorrectDataRandomPickerManhattanDist " << algo->getNumberOfIterations() << std::endl;
        delete distance;
        delete picker;
        delete space;
        delete algo;
    }
}
