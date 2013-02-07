#include <QtCore/QCoreApplication>
#include "models.hpp"
#include "KMeans.hpp"
#include "kmeanstriangle.hpp"
#include "spaces/pointsspace.h"

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
	QTextStream out(stdout);
	QFile clustersData("clusters.log");
	clustersData.open(QFile::WriteOnly);
	QTextStream stream(&clustersData);
	ClusterId num_clusters = 5;
	PointId num_points = 300;
	Dimensions num_dimensions = 200;

	PointsSpace *ps = 0;
	ps = new PointsSpace(num_points, num_dimensions);
	//std::cout << "PointSpace" << ps;

	KMeans clusters(num_clusters, 5, (AbstractPointsSpace*)ps);
	KMeansTriangle traingle(num_clusters, 5, (AbstractPointsSpace*)ps);
	clusters.setDistanceFunction(&cosinDist);
	QElapsedTimer etimer;
	etimer.start();
	clusters.executeAlgorithm();

	out << "elapsed: " << etimer.elapsed() << "ms" << endl;
	out << "distnace counter calls: " << clusters.getDistancesCallCount() << endl;
	out << "used iterations: " << clusters.getUsedIterationsCount() << endl;
	out << "distances calls per iteration: " << clusters.getDistancesCallCount() / clusters.getUsedIterationsCount() << endl;
	out.flush();
	stream << "K-Means" << endl;
	clusters.printClusters(stream);

	QElapsedTimer e1timer;
	e1timer.start();
	traingle.executeAlgorithm();


	out << "elapsed: " << e1timer.elapsed() << "ms" << endl;
	out << "distnace counter calls: " << traingle.getDistancesCallCount() << endl;
	out << "used iterations: " << traingle.getUsedIterationsCount() << endl;
	out << "conditions counter: " << traingle.getConditionsUseCount() << endl;
	out << "distances calls per iteration: " << traingle.getDistancesCallCount() / traingle.getUsedIterationsCount() << endl;
	out.flush();
	stream << "K-Means Traingle" << endl;
	traingle.printClusters(stream);
	stream << endl << "Diffs: " << endl;
	traingle.printDifferences(&clusters, stream);
	stream.flush();
	clustersData.close();
}

void testDistances()
{
	QTextStream out(stdout);
	out << endl;
	PointId num_points = 2000;
	Dimensions num_dimensions = 52;

	PointsSpace ps(num_points, num_dimensions);

	QElapsedTimer etimer;
	etimer.start();
	for(int i=0; i<1000; ++i)
		cosinDist(ps.getPoint(2*i), ps.getPoint(2*i+1));

	out << "elapsed 1000 cosin: " << etimer.elapsed() << "ms" << endl;
	out.flush();

	QElapsedTimer e1timer;
	e1timer.start();
	for(int i=0; i<1000; ++i)
		euclideanDist(ps.getPoint(2*i), ps.getPoint(2*i+1));

	out << "elapsed 1000 euclidean: " << e1timer.elapsed() << "ms" << endl;
	out.flush();
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
	testClustering();
	testDistances();
	system("pause");
	return EXIT_SUCCESS;

//    return a.exec();
}
