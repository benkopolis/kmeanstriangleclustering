#include "main.hpp"
#include "commons/sparsepoint.h"

QTextStream* m_globalLogger = 0;

double dotMatrixes(AbstractPoint const * const a, AbstractPoint const * const b)
{
	Distance result = 0;
    for(const unsigned d1 : a->getKeys())
	{
        for(const unsigned d2 : b->getKeys())
        {
            result = result + (*a)[d1] * (*b)[d2];
        }
	}
	return result;
}

Distance cosinDist(AbstractPoint const * const p, AbstractPoint const * const q)
{
	return 1.0 - (dotMatrixes(p, q) / sqrt(dotMatrixes(p, p)) * sqrt(dotMatrixes(q, q)));
}

Distance euclideanDist(AbstractPoint* p, AbstractPoint* q)
{
	long double sigma = 0.0;
    for(int i=0; i<p->size() && i<q->size(); ++i)
	{
        sigma = sigma + (long double)(((*p)[i] - (*q)[i])*((*p)[i] - (*q)[i]));
	}
	return sqrt((double)sigma);
}

void produceClusteringData()
{
    throw 1;
}

void createTfIdfFile(int argc, char *argv[])
{
    StemmedFileInMemoryParser parser;
    QTextStream out(stdout);
    if(argc != 4)
    {
        out << "Please give 2 more args: input file name and output file name" << endl;
        return;
    }
    QElapsedTimer e1timer;
    e1timer.start();
    parser.fillWithData(argv[2]);
    parser.countTfidfAndStoreInFile(argv[3]);
    QString kwFile(argv[3]);
    kwFile = kwFile.replace("tfidf", "tfidfKW");
    parser.countKeyWordsTfidfAndStoreInFile(kwFile);
    out << "Elapsed: " << e1timer.elapsed() << endl;
}


QString getOutputFileName(QString input, QString fileType,
                          int num_clusters, int num_iters)
{
    input.replace("tfidf", fileType);
    input.replace("data", "data/out");
    QString appendix = QString("%1g%2i-out").arg(QString("%1").arg(num_clusters),
                                                 QString("%1").arg(num_iters));
    return input.replace("out", appendix);
}

QString getPreRandFileName(QString input, int num_clusters,
                           int num_iters)
{
    return getOutputFileName(input, "prerand", num_clusters, num_iters);
}

QString getResultsFileName(QString input, int num_clusters,
                           int num_iters)
{
    return getOutputFileName(input, "results", num_clusters, num_iters);
}

QString getCentroidsFileName(QString input, int num_clusters,
                             int num_iters)
{
    return getOutputFileName(input, "centroids", num_clusters, num_iters);
}

void printManForComparsion(QTextStream& out)
{
    out << "Please provide more arguments:" << endl
        << "First option: -f input-data-file" << endl <<
           "Second option: -random num-dimensions num-points" << endl;
}

template<typename T>
AbstractPointsSpace<T> *generateProperPointSpace(char *argv[], QTextStream& out)
{
    Utils::Derived_from<T, AbstractPoint> d;
    AbstractPointsSpace<T>* ps = 0;
    if(!qstrcmp(argv[3], "-f"))
    {
        QString dataFile(argv[4]);
        ps = new PointsSpace<T>();
        ps->loadPointsSpace(dataFile);
    }
    else if(!qstrcmp(argv[3], "-random"))
    {
        bool okPoints = false, okDimensions = false;
        QString npoints(argv[5]), ndimensions(argv[4]);
        unsigned int num_points = npoints.toInt(&okPoints),
                num_dimensions = ndimensions.toInt(&okDimensions);
        if(!okDimensions || !okPoints)
        {
            out << "Both arguments num-dimensions and num-points need to be valid integer numbers." << endl;
                   return 0;
        }

        ps = new PointsSpace<T>(num_points, num_dimensions);
    }
    return ps;
}

void man()
{
    QTextStream out(stdout);
    out << "please add args:" << endl;
    out << "-tfidf input_file_name output_file_name" << endl
        << "\t for genereting tfidf file based on stemmed documents set." << endl;
    out << "-res input_file_name output_prerand_file_name output_results_file_name" << endl
        << "\t for generating results of clustering, pre rand indexes and mean square error." << endl;
    out << "-mse tfidf_file exisitng_results_file" << endl
        << "\t for generating mean square error base on tfidf file and results of clustering tfidf vectors from this file." << endl;
}

int main(int argc, char *argv[])
{
    QFile file("logs/full.log");
    bool globalLogFileOpened = file.open(QFile::WriteOnly);
    if(globalLogFileOpened)
        m_globalLogger = new QTextStream(&file);
    else
        m_globalLogger = new QTextStream(stderr);
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
//    testArgs();
    testClustering();
    if(argc < 2)
        man();
    else if(!qstrcmp(argv[1], "-tfidf"))
        createTfIdfFile(argc, argv);
    else if(!qstrcmp(argv[1], "-res"))
        generateResults(argc, argv);
    else if(!qstrcmp(argv[1], "-mse"))
        countMeanSquareErrorFromResultFile(argc, argv);
    else if(!qstrcmp(argv[1], "-cmp"))
        comapareDifferentKmeans(argc, argv);
    else
        man();
    m_globalLogger->flush();
    delete m_globalLogger;
    file.close();
	return EXIT_SUCCESS;

}
