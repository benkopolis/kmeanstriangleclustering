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
#include "models.hpp"
#include "spaces/abstractpointsspace.h"
#include "distances/abstractdistance.h"
#include "commons/partitiondata.h"
#include "commons/abstractpoint.h"

class KMeans
{
public:

    friend class KMeansComparer;

    KMeans(ClusterId nclusters, unsigned int numIters,
           AbstractPointsSpace<AbstractPoint>* ps);

	~KMeans();

protected:

    PartitionData* partitionData;

    unsigned int iterationsCount__;
    AbstractPointsSpace<AbstractPoint>* ps__; // the point space
    mutable unsigned distances_call_count__;
	ClusterId num_clusters__; // number of clusters
    unsigned used_iterations__;
    QList<QString> iterations_states__;
    bool store_states__;
    unsigned int num_moved__;
	Dimensions num_dimensions__; // the dimensions of vectors
	PointId num_points__; // total number of points

    Centroids centroids__;
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

    void printIterationStates(QTextStream& log);

	virtual void executeAlgorithm();

	inline unsigned getDistancesCallCount() const {
		return distances_call_count__;
	}

	inline unsigned getUsedIterationsCount() const {
		return used_iterations__;
	}

    static inline void setGlobarLoger(QTextStream* globalLogger)
    {
#ifdef LOG_ALL
        m_globalLogger = globalLogger;
#endif
    }

    inline unsigned int getMovedCount() const { return num_moved__; }
    Distance getWeightOfConnecting(PointId p, const QSet<PointId> *set) const;
    int getTemporaryGroupsSize() const;
    Distance meanSquareError();

protected:

    virtual void move_point(PointId pid, ClusterId to_cluster);

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
