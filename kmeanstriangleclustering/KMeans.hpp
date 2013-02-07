/*
 * KMeans.hpp
 *
 *  Created on: 12-12-2012
 *      Author: zby
 */

#ifndef KMEANS_HPP_
#define KMEANS_HPP_

#include <climits>
#include <cmath>
#include <QDateTime>
#include "models.hpp"
#include "spaces/abstractpointsspace.h"



class KMeans {
protected:

	distanceFunc distance__;
	unsigned used_iterations__;
	unsigned distances_call_count__;
	ClusterId num_clusters__; // number of clusters
	AbstractPointsSpace* ps__; // the point space
	Dimensions num_dimensions__; // the dimensions of vectors
	PointId num_points__; // total number of points
	ClustersToPoints clusters_to_points__;
	PointsToClusters points_to_clusters__;
	Centroids centroids__;
	unsigned int iterationsCount__;

public:

	KMeans(ClusterId nclusters, unsigned int numIters, AbstractPointsSpace* ps) :
			num_clusters__(nclusters), iterationsCount__(numIters), ps__(ps),
		distances_call_count__(0), used_iterations__(0)
	{
		ClusterId i = 0;
		Dimensions dim;
		num_dimensions__ = ps->getNumDimensions();
		num_points__ = ps->getNumPoints();
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
	~KMeans();

	virtual void executeAlgorithm();

	inline void setDistanceFunction(distanceFunc f) {
		distance__ = f;
	}
	inline distanceFunc getDistanceFunction() const {
		return distance__;
	}

	inline unsigned getDistancesCallCount() const {
		return distances_call_count__;
	}

	inline unsigned getUsedIterationsCount() const {
		return used_iterations__;
	}

	void printClusters(QTextStream& stream) const;

	void printDifferences(const KMeans* from, QTextStream& stream) const;

protected:

	Distance dotMatrixes(Point a, Point b) {
		Distance result = 0;
		foreach (Coord c, a) {
			foreach (Coord i, b)
				result = result + c * i;
		}
		return result;
	}


	Distance cosinDist(Point p, Point q) {
		++distances_call_count__;

		long double sigma = 0.0;
		for(int i=0; i<p.size() && i<q.size(); ++i)
		{
			sigma = sigma + (long double)((p[i] - q[i])*(p[i] - q[i]));
		}
		return sqrt((double)sigma);
		// cosin distance
//		return 1.0
//				- (dotMatrixes(p, q) / sqrt(dotMatrixes(p, p))
//						* sqrt(dotMatrixes(q, q)));
	}

	//
	// Zero centroids
	//
	virtual void zero_centroids();

	//
	// Zero centroids
	//
	void compute_centroids();

	//
	// Initial partition points among available clusters
	//
	virtual void initial_partition_points();

}
;

#endif /* KMEANS_HPP_ */
