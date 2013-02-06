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

// This class stores all the points available in the model
//
class PointsSpace {
public:

	//
	// Dump collection of points
	//
	friend std::ostream& operator <<(std::ostream& os, PointsSpace & ps) {

		PointId i = 0;
		foreach (Point p, ps.points__) {
			os << "point[" << i++ << "]=" << p << '\n';
		}
		return os;
	}

	PointsSpace()
	{

	}

	PointsSpace(PointId num_points, Dimensions num_dimensions) :
			num_points__(num_points), num_dimensions__(num_dimensions) {
		init_points();
	}

	PointsSpace(const PointsSpace& reference) {
		num_points__ = reference.num_points__;
		num_dimensions__ = reference.num_dimensions__;
		points__ = reference.points__;
	}

	inline const PointId getNumPoints() const {
		return num_points__;
	}
	inline const PointId getNumDimensions() const {
		return num_dimensions__;
	}
	inline const Point& getPoint(PointId pid) const {
		return points__[pid];
	}

	void dumpToFile(QString fileName);

	inline void pushBackPoint(Point p)
	{
		points__.push_back(p);
	}

private:
	//
	// Init collection of points
	//
	void init_points() {
		srand(QDateTime::currentMSecsSinceEpoch());
		for (PointId i = 0; i < num_points__; i++) {
			Point p;
			for (Dimensions d = 0; d < num_dimensions__; d++) {
				p.push_back((double)(rand() % 10)/10.0);
			}
			points__.push_back(p);

			//std::cout << "pid[" << i << "]= (" << p << ")" << std::endl;
		}
	}

	PointId num_points__;
	Dimensions num_dimensions__;
	Points points__;
};

class KMeans {
protected:

	distanceFunc distance__;
	unsigned used_iterations__;
	unsigned distances_call_count__;
	ClusterId num_clusters__; // number of clusters
	PointsSpace ps__; // the point space
	Dimensions num_dimensions__; // the dimensions of vectors
	PointId num_points__; // total number of points
	ClustersToPoints clusters_to_points__;
	PointsToClusters points_to_clusters__;
	Centroids centroids__;
	unsigned int iterationsCount__;

public:

	KMeans(ClusterId nclusters, unsigned int numIters, PointsSpace ps) :
			num_clusters__(nclusters), iterationsCount__(numIters), ps__(ps),
		distances_call_count__(0), used_iterations__(0)
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

protected:
	/*
	 def dot_matrixes(a, b):
	 """
	 Returns result of multiplication a with b
	 """
	 result = 0
	 for ia in a.keys():
	 if ia in b.keys():
	 result = result + b[ia]  * a[ia]
	 return result
	 */

	Distance dotMatrixes(Point a, Point b) {
		Distance result = 0;
		foreach (Coord c, a) {
			foreach (Coord i, b)
				result = result + c * i;
		}
		return result;
	}

	/*
	 def cosine_distance(u, v):
	 """
	 Returns the cosine of the angle between vectors v and u. This is equal to
	 u.v / |u||v|.
	 """
	 return 1.0 - (dot_matrixes(u, v) / (math.sqrt(dot_matrixes(u, u)) * math.sqrt(dot_matrixes(v, v))))
	 */

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
