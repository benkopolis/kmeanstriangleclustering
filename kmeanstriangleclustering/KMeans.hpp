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
#include <QList>
#include <QThread>
#include <QMutex>
#include "models.hpp"
#include "spaces/abstractpointsspace.h"


class KMeansComparer;


class KMeans : public QThread
{
public:

    friend class KMeansComparer;

	enum DistanceType
	{
		Euclidean = 0,
		Cosin = 1,
		Hamming = 2
	};

    enum AlgorithmPosition
    {
        None = -1,
        InitialClusters = 0,
        CentersComputed = 1,
        DistancesCounted = 2,
        EndLoop = 3
    };

    KMeans(ClusterId nclusters, unsigned int numIters,
           AbstractPointsSpace* ps, bool store=false,
           KMeansComparer *monitor=0);

	~KMeans();

protected:

    volatile AlgorithmPosition _algorithmPosition;
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
	Distances all_distances__;

	DistanceType distance_type__;

    KMeansComparer* monitor__;
    QMutex mutex;

public:

	virtual void executeAlgorithm();

    virtual void run();

    inline AlgorithmPosition getAlgorithmPosition() {
        return _algorithmPosition;
    }

	inline void setDistanceType(DistanceType type) {
		distance_type__ = type;
	}

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

	inline QList<QString> getIterationsStates() const
	{
		return this->iterations_states__;
	}

	inline unsigned int getMovedCount() const { return num_moved__; }

	void countPreRandIndex();
	bool storePreRandIndex(QString fileName) const;
	void printClustersSize(QTextStream& stream) const;

	Distance meanSquareError();

protected:

	QList<QString> iterations_states__;
	bool store_states__;
	QHash<QPair<PointId, PointId>, bool> pre_rand_index__;
	unsigned int num_moved__;

	void storeCurrentIterationState();

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

		if(distance_type__ == Hamming)
		{
			for(int i=0; i<p.size() && i<q.size(); ++i)
				sigma += fabs(p[i] - q[i]);
			return sigma;
		}
		else if(distance_type__ == Euclidean)
		{
			for (int i=0; i<p.size() && i<q.size(); ++i)
			{
				if (p.contains(i) && q.contains(i))
					sigma = sigma + (long double)((p[i] - q[i])*(p[i] - q[i]));
				else if (p.contains(i))
					sigma = sigma + p[i]*p[i];
				else if (q.contains(i))
					sigma = sigma + q[i]*q[i];
			}
			return sqrt((double)sigma);
		}
		if(distance_type__ == Cosin)
			return 1.0 - (dotMatrixes(p, q) / sqrt(dotMatrixes(p, p))
						* sqrt(dotMatrixes(q, q)));
	}

	//
	// Zero centroids
	//
	virtual void zero_centroids();

	//
	// Zero centroids
	//
	void compute_centroids(QTextStream& log);

	//
	// Initial partition points among available clusters
	//
	virtual void initial_partition_points();

}
;

#endif /* KMEANS_HPP_ */
