#include <QtCore/QCoreApplication>
#include "models.hpp"
#include "KMeans.hpp"
#include "kmeanstriangle.hpp"


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

void testClustering()
{
	QFile clustersData("clusters.log");
	clustersData.open(QFile::Append | QFile::WriteOnly);
	QTextStream stream(&clustersData);
	ClusterId num_clusters = 10;
	PointId num_points = 3000;
	Dimensions num_dimensions = 200;

	PointsSpace ps(num_points, num_dimensions);
	//std::cout << "PointSpace" << ps;

	KMeans clusters(num_clusters, 15, ps);
	KMeansTriangle traingle(num_clusters, 15, ps);
	clusters.setDistanceFunction(&cosinDist);
	QElapsedTimer etimer;
	etimer.start();
	clusters.executeAlgorithm();

	std::cout << "elapsed: " << etimer.elapsed() << "ms\n";
	std::cout << "distnace counter calls: " << clusters.getDistancesCallCount() << "\n";
	std::cout << "used iterations: " << clusters.getUsedIterationsCount() << "\n";
	std::cout.flush();
	clusters.printClusters(stream);

	QElapsedTimer e1timer;
	e1timer.start();
	traingle.executeAlgorithm();


	std::cout << "elapsed: " << e1timer.elapsed() << "ms\n";
	std::cout << "distnace counter calls: " << traingle.getDistancesCallCount() << "\n";
	std::cout << "used iterations: " << traingle.getUsedIterationsCount() << "\n";
	std::cout << "conditions counter: " << traingle.getDistancesCallCount() << "\n";
	std::cout.flush();
	traingle.printClusters(stream);
	stream.flush();
	clustersData.close();
}

void testDistances()
{
	std::cout << "\n";
	PointId num_points = 2000;
	Dimensions num_dimensions = 200;

	PointsSpace ps(num_points, num_dimensions);

	QElapsedTimer etimer;
	etimer.start();
	for(int i=0; i<1000; ++i)
		cosinDist(ps.getPoint(2*i), ps.getPoint(2*i+1));

	std::cout << "elapsed 1000 cosin: " << etimer.elapsed() << "ms\n";
	std::cout.flush();

	QElapsedTimer e1timer;
	e1timer.start();
	for(int i=0; i<1000; ++i)
		euclideanDist(ps.getPoint(2*i), ps.getPoint(2*i+1));

	std::cout << "elapsed 1000 euclidean: " << e1timer.elapsed() << "ms\n";
	std::cout.flush();
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

	testClustering();
	testDistances();
	char readKey;
	std::cin >> readKey;

	return EXIT_SUCCESS;

//    return a.exec();
}
