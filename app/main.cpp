#include "main.hpp"
#include "algorithms/kmeansalgorithm.h"
#include "analysis/randindexprocessor.h"
#include "commons/sparsepoint.h"
#include "commons/globals.h"
#include "commons/partitiondata.h"
#include "commons/centersdata.h"
#include "commons/logger.h"
#include "distances/cosinedistance.h"
#include "distances/euclideandistance.h"
#include "distances/hamiltondistance.h"
#include "distances/manhattandistance.h"



#include "pickers/randomcenterpicker.h"
#include "pickers/dimensionbasedcenterspicker.h"
#include "pickers/graphcentersandclusterspicker.h"
#include "pickers/sequentialcenterspicker.h"
#include "readers/normalizedformatdatareader.h"
#include "spaces/normalizedpointsspace.h"
#include "tfidf/stemmedfileinmemoryparser.h"

#include <cstring>
#include <string>
#include <cstdlib>
#include <iostream>

void createTfIdfFile(int argc, char *argv[])
{
    if (argc < 3) // invalid
        throw "Not enough arguments";

    StemmedFileInMemoryParser parser;
    logger::log("Created parser");
    char *stemFile = NULL;
    char *stopOut = NULL;
    char *stopIn = NULL;
    char *tfidfFile = NULL;
    double ratio, docfreq;
    for(unsigned i = 1; i < argc; i += 2)
    {
        if (!strcmp(argv[i], "-stem"))
            stemFile = argv[i+1];
        else if (!strcmp(argv[i], "-stop"))
            stopOut = argv[i+1];
        else if (!strcmp(argv[i], "-istop"))
            stopIn = argv[i+1];
        else if(!strcmp(argv[i], "-tfidf"))
            tfidfFile = argv[i+1];
        else if(!strcmp(argv[i], "-min_variation"))
            ratio = atof(argv[i+1]);
        else if(!strcmp(argv[i], "-min_docfreq"))
            docfreq = atof(argv[i+1]);
    }
    logger::log("Assigned names - going to load data");

    LoadDataArgs args;
    args.changeRatio = ratio;
    args.fileName = stemFile;
    args.stopWordsDict = stopIn;
    args.stopWordsStore = stopOut;
    args.docFreqPerc = docfreq;
    logger::log("Loading data");
    parser.loadData(args);
    logger::log("Counting tfidf");
    parser.countTfidf();
    logger::log("Storing data");
    parser.storeTfidfInFile(tfidfFile);
    logger::log("Getting terms", __LINE__, __FILE__);
    logger::log(parser.get_terms().c_str());
}

void performClustering(int argc, char *argv[])
{
    if (argc < 6)
        std::cerr << "Too few arguments to cluster!!!" << std::endl;
    AbstractDistance* distance = nullptr;
    AbstractCentersPicker<SparsePoint>* picker = nullptr;
    NormalizedFormatDataReader reader;
    char *resFile = nullptr;
    char *tfidfFile = nullptr;
    unsigned clusters = 0, iterations = 0;
    for(unsigned i = 1; i < argc; ++i)
    {
        if (!strcmp(argv[i], "-input"))
            tfidfFile = argv[i+1];
        else if (!strcmp(argv[i], "-out"))
            resFile = argv[i+1];
        else if (!strcmp(argv[i], "-rand"))
            picker = new RandomCenterPicker<SparsePoint>();
        else if (!strcmp(argv[i], "-seq"))
            picker = new SequentialCentersPicker<SparsePoint>();
        else if (!strcmp(argv[i], "-dim"))
            picker = new DimensionBasedCentersPicker<SparsePoint>();
        else if (!strcmp(argv[i], "-graph"))
            picker = new GraphCentersAndClustersPicker<SparsePoint>();
        else if (!strcmp(argv[i], "-iter"))
            iterations = std::strtoul(argv[i+1], nullptr, 0);
        else if (!strcmp(argv[i], "-clusters"))
            clusters = std::strtoul(argv[i+1], nullptr, 0);
        else if (!strcmp(argv[i], "-dcos"))
            distance = new CosineDistance();
        else if (!strcmp(argv[i], "-deuc"))
            distance = new EuclideanDistance();
        else if (!strcmp(argv[i], "-dham"))
            distance = new HamiltonDistance();
        else if (!strcmp(argv[i], "-dman"))
            distance = new ManhattanDistance();
    }
    AbstractPointsSpace<SparsePoint> * space = reader.readPointSpaceFromFile(tfidfFile);
    /* Init DensePoint keys */
    Globals::DIMENSIONS = space->getNumDimensions();
    DensePoint::InitializeKeys(Globals::DIMENSIONS);
    /* Construct grouping algo */
    KMeansAlgorithm<SparsePoint> * algo =
            new KMeansAlgorithm<SparsePoint>(distance, picker, space, 10, 25);
    algo->execute();
    const PartitionData* partData = algo->getPartitionData();
    partData->printClustersTransposed(resFile);
    PartitionData* original = space->convertTo(clusters);
    RandIndexProcessor rand_proc;
    double rand = rand_proc.process(partData, original);
    std::cout << "Rand index: " << rand << std::endl;
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
    std::cout << "-stem stemmed_file_name -stop stop_wrods_file_name -tfidf output_file_name -min_variation double_number -min_docfreq -istop stop_words_file_name" << std::endl
        << "\t\t -ratio is used when generating stop words to determine what should be acceptance ratio for a stop word" << std::endl
        << "\t\t where min_variation is a minimal variation on the word allowed (if too low the word is considered meaningless)." << std::endl
        << "\t\t and where min_docfreq is a percentage of documents in which word has to appear to be considered meaningfull." << std::endl
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

    logger::init_logger(std::cerr);
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
    logger::close_logger();
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
