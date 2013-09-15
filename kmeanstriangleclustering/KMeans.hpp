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
#include <QMultiMap>
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
        Hamming = 2,
        HammingSimplified = 3
	};

    enum AlgorithmPosition
    {
        None = -1,
        InitialClusters = 0,
        CentersComputed = 1,
        DistancesCounted = 2,
        EndLoop = 3
    };

    enum InitialPartitionType
    {
        Sequential = 0,
        MinimalNumberOfDimensions = 1,
        DeterminigNumberOfClusters = 2
    };

    KMeans(ClusterId nclusters, unsigned int numIters,
           AbstractPointsSpace* ps, bool store=false,
           KMeansComparer *monitor=0);

	~KMeans();

protected:

    volatile AlgorithmPosition _algorithmPosition;
	distanceFunc distance__;
    unsigned int iterationsCount__;
    AbstractPointsSpace* ps__; // the point space
	unsigned distances_call_count__;
	ClusterId num_clusters__; // number of clusters
    unsigned used_iterations__;
	Dimensions num_dimensions__; // the dimensions of vectors
	PointId num_points__; // total number of points
	ClustersToPoints clusters_to_points__;
	PointsToClusters points_to_clusters__;
	Centroids centroids__;
	Distances all_distances__;

	DistanceType distance_type__;
    KMeansComparer* monitor__;
    QMutex mutex;
    InitialPartitionType _initial_partition_type;
    QList<QList<Distance> > points_distances__;
    QMultiMap<Distance, QPair<PointId, PointId> > sorted_edges__;
    QList<QPair<QSet<PointId>, Distance> > temporary_groups__;

public:

    inline void setInitialPartitionType(InitialPartitionType type) { _initial_partition_type = type; }

    void testInitialPartitioning(InitialPartitionType type);

    void printIterationStates(QTextStream& log);

	virtual void executeAlgorithm();

    virtual void run();

    inline void setMonitor(KMeansComparer *comparer) { monitor__ = comparer; }

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
    bool printClusteringResults(QString fileName) const;
    bool fillWithResults(QString fileName);
    Distance getWeightOfConnecting(PointId p, QSet<PointId> set);
    int getTemporaryGroupsSize();


	Distance meanSquareError();

protected:

	QList<QString> iterations_states__;
	bool store_states__;
	QHash<QPair<PointId, PointId>, bool> pre_rand_index__;
	unsigned int num_moved__;

    virtual void storeCurrentIterationState();

    Distance dotMatrixes(const Point& a, const Point& b);

    QSet<PointId> getUniqueUnion(QList<PointId> one, QList<PointId> two);
    Distance countDistance(const Point& p, const Point& q);
    Distance euclideanDistance(const Point& p, const Point& q);
    Distance hammingDistance(const Point& p, const Point& q);
    Distance hammingSimplified(const Point& p, const Point& q);
    Distance cosineDistance(const Point& p, const Point& q);

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

    void sequential_partition_points();
    void minimal_dimensions_partitions_points();
    void determinig_number_of_clusters_partition_points();
    void fillPointsDistances();
}
;

#endif /* KMEANS_HPP_ */
