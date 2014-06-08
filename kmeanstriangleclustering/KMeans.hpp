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
    mutable unsigned distances_call_count__;
	ClusterId num_clusters__; // number of clusters
    unsigned used_iterations__;
    QList<QString> iterations_states__;
    bool store_states__;
    QHash<QPair<PointId, PointId>, bool> pre_rand_index__;
    unsigned int num_moved__;
	Dimensions num_dimensions__; // the dimensions of vectors
	PointId num_points__; // total number of points
	ClustersToPoints clusters_to_points__;
	PointsToClusters points_to_clusters__;
	Centroids centroids__;
	DistanceType distance_type__;
    KMeansComparer* monitor__;
    InitialPartitionType _initial_partition_type;
    unsigned int dimensions_delta__;
    QMutex mutex;
    QHash<PointId, QHash<PointId, Distance>* > points_distances__;
    //QMultiMap<Distance, QPair<PointId, PointId>* > sorted_edges__;
    QHash<PointId, QMultiMap<Distance, PointId>* > distances_to_points__;
    QHash<PointId, QPair<QSet<PointId>*, Distance>* > temporary_groups__;

    static inline void log_all(const QString& message)
    {
#ifdef LOG_ALL
        *m_globalLogger << endl << message << endl;
#endif
    }

    static inline void log_one_line(const QString& message)
    {
#ifdef LOG_ALL
        *m_globalLogger << message;
#endif
    }

private:

    Distances all_distances__;

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

    inline void setDimensionsDelta(unsigned int delta) {
        dimensions_delta__ = delta;
    }

    inline unsigned int getDimensionsDelta() const {
        return dimensions_delta__;
    }

    static inline void setGlobarLoger(QTextStream* globalLogger)
    {
#ifdef LOG_ALL
        m_globalLogger = globalLogger;
#endif
    }

	void printClusters(QTextStream& stream) const;

	void printDifferences(const KMeans* from, QTextStream& stream) const;

	inline QList<QString> getIterationsStates() const
	{
		return this->iterations_states__;
	}

	inline unsigned int getMovedCount() const { return num_moved__; }

	void countPreRandIndex();
    bool storePreRandIndex(const QString& fileName) const;
    void printClustersSize(QTextStream& stream) const;
    bool printClusteringResults(const QString& fileName) const;
    bool printCentroids(const QString& fileName) const;
    bool fillWithResults(const QString& fileName);
    Distance getWeightOfConnecting(PointId p, const QSet<PointId> *set) const;
    int getTemporaryGroupsSize() const;


	Distance meanSquareError();

protected:

    virtual void storeCurrentIterationState();

    Distance dotMatrixes(const Point& a, const Point& b) const;

    QSet<PointId> getUniqueUnion(const QList<PointId> &one, const QList<PointId> &two) const;
    Distance countDistance(const Point& p, const Point& q) const;
    Distance euclideanDistance(const Point& p, const Point& q) const;
    Distance hammingDistance(const Point& p, const Point& q) const;
    Distance hammingSimplified(const Point& p, const Point& q) const;
    Distance cosineDistance(const Point& p, const Point& q) const;
    Distance get_dist_p2p(PointId x, PointId y) const;
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
    QList<PointId> *iterateOverTemporaryGroupsAndAssignPoints(PointId groupId, QSet<PointId> *usedPoints, QSet<PointId> *notUsedPoints, QList<PointId> *pointsToCheck);
    void determinig_number_of_clusters_partition_points();
    void fillPointsDistances();
}
;

#endif /* KMEANS_HPP_ */
