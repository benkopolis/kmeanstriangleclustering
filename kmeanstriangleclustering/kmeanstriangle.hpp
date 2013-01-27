#ifndef KMEANSTRIANGLE_HPP
#define KMEANSTRIANGLE_HPP

#include <QFile>
#include <QTextStream>

#include "KMeans.hpp"
#include "models.hpp"

class KMeansTriangle : public KMeans
{
public:
	KMeansTriangle(ClusterId nclusters, unsigned int numIters, PointsSpace ps) :
		KMeans(nclusters, numIters, ps)
//	    ,pointsToCenters__(nclusters, QVector<Distance>(ps.getNumPoints(), 1.0))
	{
		ClusterId i = 0;
		Dimensions dim;
		num_dimensions__ = ps.getNumDimensions();
		num_points__ = ps.getNumPoints();
		for (; i < nclusters; i++) {
			Point point; // each centroid is a point
			for (dim = 0; dim < num_dimensions__; dim++)
				point.push_back(0.0);
			SetPoints set_of_points;

			// init centroids
			centroids__.push_back(point);

			// init clusterId -> set of points
			clusters_to_points__.push_back(set_of_points);
			// init point <- cluster

		}
	}

	virtual void executeAlgorithm();

	inline unsigned getConditionsUseCount() const {
		return conditions_use_counter__;
	}

protected:

	//
	// Zero centroids
	//
	void compute_centroids(bool first);

	//
	// Initial partition points among available clusters
	//
	virtual void initial_partition_points();

private:

	Distances pointsToCenters__;
	Distances centersToCenters__;
	QVector<Distance> upperBounds__;
	Distances lowerBounds__;
	QVector<bool> rVector__;
	QVector<Distance> sVector__;
	unsigned conditions_use_counter__;
};

#endif // KMEANSTRIANGLE_HPP
