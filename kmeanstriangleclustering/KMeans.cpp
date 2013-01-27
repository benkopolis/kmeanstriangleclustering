/*
 * KMeans.cpp
 *
 *  Created on: 12-12-2012
 *      Author: zby
 */

#include <boost/foreach.hpp>
#include <iostream>
#include <set>
#include <vector>
#include "KMeans.hpp"
#include "models.hpp"

//std::ostream& operator <<(std::ostream& os, PointsSpace & ps) {
//
//	PointId i = 0;
//	foreach(Point p, ps.points__){
//		os << "point[" << i++ << "]=" << p << std::endl;
//	}
//	return os;
//}

//
// Dump a point
//
std::ostream& operator <<(std::ostream& os, Point& p) {
	foreach(Coord d, p){ os << d << " ";}
return os;
}

 //
 // Dump collection of Points
 //
std::ostream& operator <<(std::ostream& os, Points& cps) {
	foreach(Point p, cps){ os<<p <<std::endl;}
return os;
}

 //
 // Dump a Set of points
 //
std::ostream& operator <<(std::ostream& os, SetPoints & sp) {

	foreach(SetPoints::value_type pid, sp){
	os << "pid=" << pid << " ";
}
return os;
};

//
// Dump ClustersToPoints
//
std::ostream& operator <<(std::ostream& os, ClustersToPoints & cp) {
	ClusterId cid = 0;
	foreach(ClustersToPoints::value_type set, cp){
	os << "clusterid[" << cid << "]" << "=("
	<< set << ")" << std::endl;
	cid++;
}
	return os;
}

//
// Dump ClustersToPoints
//
std::ostream& operator <<(std::ostream& os, PointsToClusters & pc) {
	PointId pid = 0;
	foreach(PointsToClusters::value_type cid, pc){

	std::cout << "pid[" << pid << "]=" << cid << std::endl;
	pid ++;
}
	return os;
}

//void PointsSpace::init_points() {
//	srand(23423255453);
//	for (PointId i = 0; i < num_points__; i++) {
//		Point p;
//		for (Dimensions d = 0; d < num_dimensions__; d++) {
//			p.push_back(rand() % 100);
//		}
//		points__.push_back(p);
//
//		std::cout << "pid[" << i << "]= (" << p << ")" << std::endl;
//	}
//}

KMeans::~KMeans() {
	// TODO Auto-generated destructor stub
}

//
// Zero centroids
//
void KMeans::zero_centroids() {

	foreach(Point centroid, centroids__){
	foreach(Coord d, centroid) {
		d = 0.0;
	}
}
}

//
// Compute Centroids
//
void KMeans::compute_centroids() {

	Dimensions i;
	ClusterId cid = 0;
	PointId num_points_in_cluster;
	// For each centroid
	foreach(Point centroid, centroids__){

		num_points_in_cluster = 0;

		// For earch PointId in this set
		foreach(PointId pid,
				clusters_to_points__[cid]) {

			Point p = ps__.getPoint(pid);
			//std::cout << "(" << p << ")";
			for (i=0; i<num_dimensions__; i++)
			centroid[i] += p[i];
			num_points_in_cluster++;
		}
		//
		// if no point in the clusters, this goes to inf (correct!)
		//
		for (i=0; i<num_dimensions__; i++)
		centroid[i] /= num_points_in_cluster;
		cid++;
	}
}

//
// Initial partition points among available clusters
//
void KMeans::initial_partition_points() {

	ClusterId cid;

	for (PointId pid = 0; pid < ps__.getNumPoints(); pid++) {

		cid = pid % num_clusters__;
//		std::cout << points_to_clusters__.size() << '\n';
		points_to_clusters__.push_back(cid);
		clusters_to_points__[cid].insert(pid);
	}
}

void KMeans::executeAlgorithm() {
	bool move;
	bool some_point_is_moving = true;
	unsigned int num_iterations = 0;
	PointId pid;
	ClusterId cid, to_cluster;
	Distance d, min;

	//
	// Initial partition of points
	//
	initial_partition_points();

	//
	// Until not converge
	//
	while (some_point_is_moving && num_iterations <= iterationsCount__) {

	//	std::cout << std::endl << "*** Num Iterations " << num_iterations
		//		<< std::endl << std::endl;
		some_point_is_moving = false;
		compute_centroids();

		// for each point
		for (pid = 0; pid < num_points__; pid++) {
			// distance from current cluster
			min = cosinDist(centroids__[points_to_clusters__[pid]],
					ps__.getPoint(pid));

			// foreach centroid
			cid = 0;
			move = false;
			foreach(Centroids::value_type c, centroids__){

			d = cosinDist(c, ps__.getPoint(pid));
			if (d < min) {
				min = d;
				move = true;
				to_cluster = cid;

				// remove from current cluster
				clusters_to_points__[points_to_clusters__[pid]].remove(pid);

				some_point_is_moving = true;
				//std::cout << "\tcluster=" << cid
			//	<< " closer, dist=" << d << std::endl;
			}
			cid++;
		}

		//
		// move towards a closer centroid
		//
			if (move) {
				// insert
				points_to_clusters__[pid] = to_cluster;
				clusters_to_points__[to_cluster].insert(pid);
				//std::cout << "\t\tmove to cluster=" << to_cluster << std::endl;
			}
		}

		num_iterations++;
	} // end while (some_point_is_moving)

}
