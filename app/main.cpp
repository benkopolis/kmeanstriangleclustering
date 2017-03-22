#include "main.hpp"
#include "commons/globals.h"
#include "commons/logger.h"

#include <cstring>
#include <string>
#include <cstdlib>
#include <iostream>

#include "processors/obsoleteclusteringprocessor.h"
#include "processors/obsoletetfidfprocessor.h"
#include "processors/randprocessor.h"
#include "processors/silhouetteprocessor.h"
#include "processors/variationofinformationprocessor.h"

void createTfIdfFile(int argc, char *argv[])
{
    ObsoleteTfIdfProcessor proc(argc, argv);
    proc.process();
}

void performClustering(int argc, char *argv[])
{
    ObsoleteClusteringProcessor proc(argc, argv);
    proc.process();
}

void produceClusteringData()
{
    throw 1;
}

void countSilhouette(int argc, char** argv)
{
    SilhouetteProcessor proc(argc, argv);
    proc.process();
}

void countRand(int argc, char** argv)
{
    RandProcessor proc(argc, argv);
    proc.process();
}

void countVariationOfInformation(int argc, char** argv)
{
    VariationOfInformationProcessor proc(argc, argv);
    proc.process();
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
    logger::disable_logger();
    std::cerr << "started" << std::endl;
    std::cerr.flush();
    if(argc < 2)
        man();
    else if(!strcmp(argv[1], "-stem") || !strcmp(argv[1], "-tfidf") || !strcmp(argv[1], "-stop"))
        createTfIdfFile(argc, argv);
    else if(!strcmp(argv[1], "-input"))
        performClustering(argc, argv);
    else if(!strcmp(argv[1], "-silhouette"))
        countSilhouette(argc, argv);
    else if(!strcmp(argv[1], "-randindex"))
        countRand(argc, argv);
    else if(!strcmp(argv[1], "-varoi"))
        countVariationOfInformation(argc, argv);
//    else if(!strcmp(argv[1], "-res"))
//        generateResults(argc, argv);
//    else if(!strcmp(argv[1], "-mse"))
//        countMeanSquareErrorFromResultFile(argc, argv);
//    else if(!strcmp(argv[1], "-cmp"))
//        comapareDifferentKmeans(argc, argv);
    else
        man();
    std::cerr << "done" << std::endl;
    std::cout << "done" << std::endl;
    std::cerr.flush();
    std::cout.flush();
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
