#include "main.hpp"

QTextStream* m_globalLogger = 0;

Distance dotMatrixes(Point a, Point b)
{
	Distance result = 0;
	foreach(Coord c, a)
	{
		foreach(Coord i, b)
			result = result + c*i;
	}
	return result;
}

Distance cosinDist(Point p, Point q)
{
	return 1.0 - (dotMatrixes(p, q) / sqrt(dotMatrixes(p, p)) * sqrt(dotMatrixes(q, q)));
}

Distance euclideanDist(Point p, Point q)
{
	long double sigma = 0.0;
	for(int i=0; i<p.size() && i<q.size(); ++i)
	{
		sigma = sigma + (long double)((p[i] - q[i])*(p[i] - q[i]));
	}
	return sqrt((double)sigma);
}

void produceClusteringData()
{
    throw 1;
}

void executeAndPrintClusteringResults(QTextStream* stream, QTextStream& out, KMeans* clusters, QString message)
{
    executeAndPrintClusteringResults(stream, out, *clusters, message);
}

void executeAndPrintClusteringResults(QTextStream* stream, QTextStream& out, KMeans& clusters, QString message)
{
    QElapsedTimer etimer;
    out << endl << message << endl;
    etimer.start();
    clusters.executeAlgorithm();
    out << "elapsed: " << etimer.elapsed() << "ms" << endl;
    out << "distnace counter calls: " << clusters.getDistancesCallCount() << endl;
    out << "used iterations: " << clusters.getUsedIterationsCount() << endl;
    out << "distances calls per iteration: " << clusters.getDistancesCallCount() / clusters.getUsedIterationsCount() << endl;
    out << "Error: " << clusters.meanSquareError() << endl;
    out << "Moved: " << clusters.getMovedCount() << endl;
    out << "Clusters: " << endl;
    out.flush();
    if(stream != 0)
        stream->flush();
}

void testClustering()
{
//	QFile outputData("output.data");
//	outputData.open(QFile::WriteOnly | QFile::Append);
	QTextStream out(stdout);
	QFile clustersData("clusters.log");
	clustersData.open(QFile::WriteOnly);
	QTextStream stream(&clustersData);
    ClusterId num_clusters = 4;

	AbstractPointsSpace *ps = 0, *ps1, *ps2;
//	ps = new NormalizedPointsSpace();
    ps = new PointsSpace();//(num_points, num_dimensions);//
    ps->loadPointsSpace("smaller_point.txt");
//	ps->loadPointsSpace("points.data");
//    ps->loadPointsSpace("small_test_point_space.txt");
    KMeans clusters(num_clusters, 10, ps, true);
    KMeansTriangle traingle(num_clusters, 10, ps, true);
//    KMeans hamming(num_clusters, 10, ps, true);
//	hamming.setDistanceType(KMeans::Hamming);
	clusters.setDistanceFunction(&cosinDist);

    executeAndPrintClusteringResults(&stream, out, clusters, "NORMAL KMEANS");

    executeAndPrintClusteringResults(&stream, out, traingle, "TRIANGLE KMEANS");
    out << "conditions counter: " << traingle.getConditionsUseCount() << endl;
    stream << endl << "KMEANS STATES" << endl;
    clusters.printIterationStates(stream);
    stream << endl << "TRAIANGLE STATES" << endl;
    traingle.printIterationStates(stream);

//	QElapsedTimer e2timer;
//	e2timer.start();
//	hamming.executeAlgorithm();
//	out << "elapsed: " << e2timer.elapsed() << "ms" << endl;
//	out << "distnace counter calls: " << hamming.getDistancesCallCount() << endl;
//	out << "used iterations: " << hamming.getUsedIterationsCount() << endl;
//	out << "distances calls per iteration: " << hamming.getDistancesCallCount() / hamming.getUsedIterationsCount() << endl;
//	out << "Error: " << hamming.meanSquareError() << endl;
//	out << "Moved: " << hamming.getMovedCount() << endl;
//	out << "Clusters: " << endl;
//	hamming.printClustersSize(out);

//	hamming.storePreRandIndex("hammingX.prtxt");
	out.flush();
	stream.flush();
	clustersData.close();
    delete ps;
	//outputData.close();
}

void testDistances()
{
	QTextStream out(stdout);
	out << endl;
	PointId num_points = 20;
	Dimensions num_dimensions = 5;

	PointsSpace ps(num_points, num_dimensions);

	QElapsedTimer etimer;
	etimer.start();
	for(int i=0; i<10; ++i)
		cosinDist(ps.getPoint(2*i), ps.getPoint(2*i+1));

	out << "elapsed 1000 cosin: " << etimer.elapsed() << "ms" << endl;
	out.flush();

	QElapsedTimer e1timer;
	e1timer.start();
	for(int i=0; i<10; ++i)
		euclideanDist(ps.getPoint(2*i), ps.getPoint(2*i+1));

	out << "elapsed 1000 euclidean: " << e1timer.elapsed() << "ms" << endl;
	out.flush();
}

void testThreadClustering()
{
    QFile outputData("output.data");
    outputData.open(QFile::WriteOnly | QFile::Append);
    QTextStream logs(&outputData);
    QTextStream out(stdout);
    QFile clustersData("clusters.log");
    clustersData.open(QFile::WriteOnly);
    QTextStream stream(&clustersData);
    ClusterId num_clusters = 4;
    PointId num_points = 30;
    Dimensions num_dimensions = 100;

    AbstractPointsSpace *ps = 0, *ps1;//, *ps2;
    //ps = new NormalizedPointsSpace();
    ps = new PointsSpace(num_points, num_dimensions);//
    //ps->loadPointsSpace("D:/korpusy/classic_data/docbyterm.tfidf.norm.txt");
//    ps->loadPointsSpace("points.data");
    ps1 = new PointsSpace(*(PointsSpace*)ps);
//    ps2 = new PointsSpace(*(PointsSpace*)ps);

    KMeansComparer* comparer = new KMeansComparer();
    KMeans * clusters = new KMeans(num_clusters, 10, ps, true);
    KMeansTriangle *traingle = new KMeansTriangle(num_clusters, 10, ps1, true);
    comparer->addAlgorithm(clusters);
    comparer->addAlgorithm(traingle);

    out << "Start" << endl;

    comparer->start();
    comparer->wait();

    logs << comparer->logs();

    delete clusters;
    delete traingle;
    delete comparer;

    out << "Done" << endl;
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

AbstractPointsSpace* generateProperPointSpace(char *argv[], QTextStream& out)
{
    AbstractPointsSpace* ps = 0;
    if(!qstrcmp(argv[3], "-f"))
    {
        QString dataFile(argv[4]);
        ps = new PointsSpace();
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

        ps = new PointsSpace(num_points, num_dimensions);
    }
    return ps;
}

void comapareDifferentKmeans(int argc, char *argv[])
{
    QTextStream out(stdout);
    if(argc < 3 || (!qstrcmp(argv[3], "-f") && argc < 4)
            || (!qstrcmp(argv[3], "-random") && argc < 5))
    {
        printManForComparsion(out);
        return;
    }

    AbstractPointsSpace *ps = 0;
    unsigned int num_clusters = 10, numIters = 10;
    if((ps = generateProperPointSpace(argv, out)) == 0)
        return;

    KMeans * clusters = new KMeans(num_clusters, numIters, ps, true);
    KMeansTriangle *traingle = new KMeansTriangle(num_clusters, numIters, ps, true);

    executeAndPrintClusteringResults(0, out, clusters, "DEFAULT KMEANS");
    executeAndPrintClusteringResults(0, out, traingle, "KMEANS TRIANGLE");
}

void generateResults(int argc, char *argv[])
{
    QTextStream out(stdout);
    if(argc < 4)
    {
        out << "Please give 2 or 3 more args:" << endl <<
               "input-data-file max-iterations num_of_clusters [optional, def:10]" << endl
            << "input file must contains 'tfidf' and 'out' strings in its name" << endl;
        return;
    }
    QElapsedTimer e1timer;
    NormalizedPointsSpace* space = new NormalizedPointsSpace();
    space->loadPointsSpace(argv[2]);
    bool ok = false;
    QString iters(argv[3]);
    int num_iters = iters.toInt(&ok);
    if(!ok)
    {
        out << "Parameter max-iterations must have an integer value!" << endl;
        return;
    }
    int num_clusters = 0;
    if(argc == 5)
    {
        QString clustersStr(argv[4]);
        num_clusters = clustersStr.toInt(&ok);
        if(!ok)
        {
            out << "Parameter num_of_clusters must have an integer value!" << endl;
            num_clusters = 10;
            return;
        }
    }
    KMeans* clusters = new KMeans(num_clusters, num_iters, space, false);
    e1timer.start();
    clusters->executeAlgorithm();
    out << "Elapsed: " << e1timer.elapsed() << endl;
    out << "Mean square error: " << clusters->meanSquareError();
}

void countMeanSquareErrorFromResultFile(int argc, char *argv[])
{
    QTextStream out(stdout);
    if(argc != 4)
    {
        out << "Please give 3 more args: tfidf file, and input results file name" << endl;
        return;
    }
    QElapsedTimer e1timer;
    NormalizedPointsSpace* space = new NormalizedPointsSpace();
    space->loadPointsSpace(argv[2]);
    KMeans* clusters = new KMeans(10, 10, space, false);
    Distance d = clusters->meanSquareError();
    out << "Elapsed: " << e1timer.elapsed() << endl;
    out << "Mean Square error: " << d << endl;
    delete clusters;
    delete space;
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

void testArgs()
{
    QTextStream out(stdout);
    QElapsedTimer e1timer;
    //PointsSpace* space = new PointsSpace(200, 3000);
    //space->savePointsSpace("test_space.txt");
    NormalizedPointsSpace* space = new NormalizedPointsSpace();
    space->loadPointsSpace("data/r8-train-tfidf-out.txt"); //  "data/r8-train-tfidf-out.txt" "small_norm_point_space.txt"
    KMeans* clusters = new KMeans(10, 10, space, false);
    e1timer.start();
    clusters->testInitialPartitioning(KMeans::MinimalNumberOfDimensions);
    out << "Elapsed: " << e1timer.elapsed() << endl;
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
