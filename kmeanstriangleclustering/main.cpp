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



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

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
	std::cout.flush();

	QElapsedTimer e1timer;
	e1timer.start();
	traingle.executeAlgorithm();


	std::cout << "elapsed: " << e1timer.elapsed() << "ms\n";
	std::cout << "distnace counter calls: " << traingle.getDistancesCallCount() << "\n";
	std::cout << "conditions counter: " << traingle.getDistancesCallCount() << "\n";
	std::cout.flush();

	char readKey;
	std::cin >> readKey;

	return EXIT_SUCCESS;

//    return a.exec();
}
