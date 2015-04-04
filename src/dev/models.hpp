/*
 * models.hpp
 *
 *  Created on: 12-12-2012
 *      Author: zby
 */

#ifndef MODELS_HPP_
#define MODELS_HPP_

#include <QtCore>
#include <QVector>
#include <QSet>
#include <QHash>
#include <QList>
#include <limits>

#define LOG_ALL 1

#ifdef LOG_ALL
#define logall(x) log_all(x)
#define logoneline(s) log_one_line(s)
#else
#define logall(x) log_all("")
#define logoneline(s) log_one_line("")
#endif

extern QTextStream* m_globalLogger;

typedef double Coord;

typedef double Distance;

typedef QHash<unsigned int, QHash<unsigned int, Distance> > Distances;
//typedef QList<QList<Distance> > Distances;

typedef QHash<unsigned int, Coord> Point;

typedef QVector<Point> Points;

typedef unsigned int Dimensions; // how many dimensions

typedef unsigned int PointId; // the id of this point

typedef unsigned int ClusterId; // the id of this cluster

typedef QSet<PointId> SetPoints; // set of points

// ClusterId -> (PointId, PointId, PointId, .... )
typedef QVector<SetPoints* > ClustersToPoints;
// PointId -> ClusterId
typedef QHash<PointId, ClusterId> PointsToClusters;
// coll of centroids
typedef QVector<Point> Centroids;

typedef Distance (*distanceFunc)(Point, Point);

struct DistancesCountData {

    DistancesCountData()
    {
        reset();
    }

    bool notCounted;
    Distance distance;

    void reset()
    {
        distance = std::numeric_limits<Distance>::max();
        notCounted = true;
    }
};

//
// Dump a point
//
std::ostream& operator <<(std::ostream& os, Point& p);

//
// Dump collection of Points
//
std::ostream& operator <<(std::ostream& os, Points& cps);

//
// Dump a Set of points
//
std::ostream& operator <<(std::ostream& os, SetPoints & sp);

//
// Dump centroids
//
std::ostream& operator <<(std::ostream& os, Centroids & cp);

//
// Dump ClustersToPoints
//
std::ostream& operator <<(std::ostream& os, ClustersToPoints & cp);

//
// Dump ClustersToPoints
//
std::ostream& operator <<(std::ostream& os, PointsToClusters & pc);

//





#endif /* MODELS_HPP_ */
