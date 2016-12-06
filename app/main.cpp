#include "main.hpp"
#include "algorithms/kmeansalgorithm.h"
#include "commons/sparsepoint.h"
#include "commons/globals.h"
#include "pickers/randomcenterpicker.h"
#include "commons/partitiondata.h"
#include "commons/centersdata.h"
#include "spaces/normalizedpointsspace.h"
#include "distances/cosinedistance.h"
#include "distances/euclideandistance.h"
#include "distances/hamiltondistance.h"
#include "distances/manhattandistance.h"
#include "readers/normalizedformatdatareader.h"
#include "tfidf/stemmedfileinmemoryparser.h"

#include <cstring>
#include <iostream>

void createTfIdfFile(int argc, char *argv[])
{
    if (argc < 3) // invalid
        throw "Not enough arguments";

    StemmedFileInMemoryParser parser;
    std::cerr << "Created parser" << std::endl;
    std::cerr.flush();
    char *stemFile = NULL;
    char *stopFile = NULL;
    char *tfidfFile = NULL;
    for(unsigned i = 1; i < argc; i += 2)
    {
        if (!strcmp(argv[i], "-stem"))
            stemFile = argv[i+1];
        else if (!strcmp(argv[3], "-stop"))
            stopFile = argv[i+1];
        else if(!strcmp(argv[i], "-tfidf"))
            tfidfFile = argv[i+1];
    }
    std::cerr << "Assigned names" << std::endl;
    std::cerr.flush();

    parser.loadData(stemFile, stopFile);
    std::cerr << "Loaded data" << std::endl;
    std::cerr.flush();
    parser.countTfidf();
    std::cerr << "Counted tfidf" << std::endl;
    std::cerr.flush();
    parser.storeTfidfInFile(tfidfFile);
    std::cerr << "Storing data" << std::endl;
    std::cerr.flush();
}

void performClustering(int argc, char *argv[])
{
    CosineDistance* distance = new CosineDistance();
    RandomCenterPicker<SparsePoint>* picker = new RandomCenterPicker<SparsePoint>();
    NormalizedFormatDataReader reader;
    char *resFile = NULL;
    char *tfidfFile = NULL;
    for(unsigned i = 1; i < argc; i += 2)
    {
        if (!strcmp(argv[i], "-input"))
            tfidfFile = argv[i+1];
        else if (!strcmp(argv[3], "-out"))
            resFile = argv[i+1];
    }
    AbstractPointsSpace<SparsePoint> * space = reader.readPointSpaceFromFile(tfidfFile);
    KMeansAlgorithm<SparsePoint,CosineDistance> * algo =
            new KMeansAlgorithm<SparsePoint, CosineDistance>(distance, picker, space, 10, 5);
    algo->execute();
    const PartitionData* partData = algo->getPartitionData();
    partData->printClusters(resFile);
    std::cerr << "KMeansCorrectDataRandomPickerCosineDist " << algo->getNumberOfIterations() << std::endl;
    delete distance;
    delete picker;
    delete space;
    delete algo;
}

void produceClusteringData()
{
    throw 1;
}


//template<typename T>
//AbstractPointsSpace<T> *generateProperPointSpace(char *argv[])
//{
//    Utils::Derived_from<T, AbstractPoint> d;
//    AbstractPointsSpace<T>* ps = 0;
//    if(!strcmp(argv[3], "-f"))
//    {
//        QString dataFile(argv[4]);
//        ps = new PointsSpace<T>();
//        ps->loadPointsSpace(dataFile);
//    }
//    else if(!strcmp(argv[3], "-random"))
//    {
//        bool okPoints = false, okDimensions = false;
//        QString npoints(argv[5]), ndimensions(argv[4]);
//        unsigned int num_points = npoints.toInt(&okPoints),
//                num_dimensions = ndimensions.toInt(&okDimensions);
//        if(!okDimensions || !okPoints)
//        {
//            std::cout << "Both arguments num-dimensions and num-points need to be valid integer numbers." << endl;
//                   return 0;
//        }

//        ps = new PointsSpace<T>(num_points, num_dimensions);
//    }
//    return ps;
//}

void man()
{
    std::cout << "please add args:" << std::endl;
    std::cout << "-stem stemmed_file_name -stop stop_wrods_file_name -tfidf output_file_name" << std::endl
        << "\t for genereting tfidf file based on stemmed documents set." << std::endl;
    std::cout << "-res input_file_name output_prerand_file_name output_results_file_name" << std::endl
        << "\t for generating results of clustering, pre rand indexes and mean square error." << std::endl;
    std::cout << "-mse tfidf_file exisitng_results_file" << std::endl
        << "\t for generating mean square error base on tfidf file and results of clustering tfidf vectors from this file." << std::endl;
}

int main(int argc, char *argv[])
{
//    testArgs();
//    testClustering();
    Globals::DIMENSIONS = 2045;
    DensePoint::InitializeKeys(Globals::DIMENSIONS);
    std::cerr << "started" << std::endl;
    std::cerr.flush();
    if(argc < 2)
        man();
    else if(!strcmp(argv[1], "-stem") || !strcmp(argv[1], "-tfidf") || !strcmp(argv[1], "-stop"))
        createTfIdfFile(argc, argv);
    else if(!strcmp(argv[1], "-input"))
        performClustering(argc, argv);
//    else if(!strcmp(argv[1], "-res"))
//        generateResults(argc, argv);
//    else if(!strcmp(argv[1], "-mse"))
//        countMeanSquareErrorFromResultFile(argc, argv);
//    else if(!strcmp(argv[1], "-cmp"))
//        comapareDifferentKmeans(argc, argv);
    else
        man();
    std::cerr << "done" << std::endl;
    std::cerr.flush();
    return EXIT_SUCCESS;

}

//int main(int argc, char **argv)
//{
//    QApplication a(argc, argv);
//    MainWindow mainWindow;
//    mainWindow.show();
//    int result = a.exec();
//    Utils::destroy();
//    return result;
//}
