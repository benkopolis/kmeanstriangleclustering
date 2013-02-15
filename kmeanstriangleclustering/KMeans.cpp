/*
 * KMeans.cpp
 *
 *  Created on: 12-12-2012
 *      Author: zby
 */

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
QTextStream& operator <<(QTextStream& os, Point& p) {
	foreach(Coord d, p){ os << d << " ";}
return os;
}

 //
 // Dump collection of Points
 //
QTextStream& operator <<(QTextStream& os, Points& cps) {
	foreach(Point p, cps){ os<<p << endl;}
return os;
}

 //
 // Dump a Set of points
 //
QTextStream& operator <<(QTextStream& os, SetPoints & sp) {

	foreach(SetPoints::value_type pid, sp){
	os << "pid=" << pid << " ";
}
return os;
};

//
// Dump ClustersToPoints
//
QTextStream& operator <<(QTextStream& os, ClustersToPoints & cp) {
	ClusterId cid = 0;
	foreach(ClustersToPoints::value_type set, cp){
	os << "clusterid[" << cid << "]" << "=("
	<< set << ")" << endl;
	cid++;
}
	return os;
}

//
// Dump ClustersToPoints
//
QTextStream& operator <<(QTextStream& os, PointsToClusters & pc) {
	PointId pid = 0;
	QTextStream cout(stdout);
	foreach(PointsToClusters::value_type cid, pc){

	cout << "pid[" << pid << "]=" << cid << endl;
	pid ++;
}
	return os;
}

//////////////////////////////////////////////
//
//  K - MEANS
//
//////////////////////////////////////////////


KMeans::KMeans(ClusterId nclusters, unsigned int numIters, AbstractPointsSpace* ps, bool store) :
		num_clusters__(nclusters), iterationsCount__(numIters), ps__(ps),
	distances_call_count__(0), used_iterations__(0), store_states__(store)
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
		QHash<PointId, Distance> hash;
		all_distances__.insert(i, hash);

		// init clusterId -> set of points
		clusters_to_points__.push_back(set_of_points);
		// init point <- cluster

	}
}

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
void KMeans::compute_centroids(QTextStream& log)
{
	Dimensions i;
	ClusterId cid = 0;
	PointId num_points_in_cluster;
	// For each centroid
	QVector<Point> means(centroids__); // implicitly shared data - const time. Copied on write.
	foreach(Point centroid, centroids__)
	{
		num_points_in_cluster = 0;
		// For earch PointId in this set
		foreach(PointId pid, clusters_to_points__[cid])
		{
			Point p = ps__->getPoint(pid);
			log << "kmeans centres: [" << pid << "]" << endl;
			for (i=0; i<num_dimensions__; i++)
			{
				means[cid][i] += p[i];
				log << "tmp means[" << cid << "][" << i << "] = " << means[cid][i] << endl;
			}
			num_points_in_cluster++;
		}
		//
		// if no point in the clusters, this goes to inf (correct!)
		//
		for (i=0; i<num_dimensions__; i++)
		{
			means[cid][i] /= num_points_in_cluster;
			log << "means[" << cid << "][" << i << "] /= " << num_points_in_cluster << " = " << means[cid][i] << endl;
		}
		cid++;
	}
	centroids__ = means;
}

//
// Initial partition points among available clusters
//
void KMeans::initial_partition_points()
{
	ClusterId cid;

	for (PointId pid = 0; pid < ps__->getNumPoints(); pid++) {

		cid = pid % num_clusters__;
//		std::cout << points_to_clusters__.size() << '\n';
		points_to_clusters__.push_back(cid);
		clusters_to_points__[cid].insert(pid);
	}
}



void KMeans::printClusters(QTextStream& stream) const
{
	int i=0;
	foreach(const SetPoints set, clusters_to_points__)
	{
		stream << i << ": ";
		foreach(const PointId point, set)
		{
			stream << point << ", ";
		}
		stream << endl;
		++i;
	}
}

void KMeans::printDifferences(const KMeans* from, QTextStream& stream) const
{
	int i=0, total = 0;
	foreach(const SetPoints set, clusters_to_points__)
	{
		stream << i << ": ";
		int diffs = 0;
		foreach(const PointId point, set)
		{
			if(from->clusters_to_points__.at(i).find(point) == from->clusters_to_points__.at(i).end())
				++diffs;
		}
		stream << diffs << "/" << from->clusters_to_points__.at(i).size() << endl;
		total += diffs;
		++i;
	}
	stream << endl << "Points with various assignment: " << total << endl
		   << "Errors %: " << ((float)total / num_points__) *100.0 << endl;
}

/**
  *
  */
void KMeans::executeAlgorithm()
{
	bool move;
	bool some_point_is_moving = true;
	unsigned int num_iterations = 0;
	PointId pid;
	ClusterId cid, to_cluster;
	Distance d, min;
	QFile log_file__("log_template.txt");
	QTextStream* log_stream__;
	if(log_file__.open(QFile::WriteOnly))// | QFile::Append))
		log_stream__ = new QTextStream(&log_file__);
	else
		log_stream__ = new QTextStream(stdout);
	//
	// Initial partition of points
	//
	initial_partition_points();

	//
	// Until not converge
	//
	while (some_point_is_moving && num_iterations <= iterationsCount__)
	{
		if(store_states__)
			this->storeCurrentIterationState();
		some_point_is_moving = false;
		compute_centroids(*log_stream__);
		for(int centerId=0; centerId < centroids__.size(); ++centerId)
			all_distances__[centerId].clear();
		// for each point
		for (pid = 0; pid < num_points__; pid++)
		{
			// distance from current cluster
			min = cosinDist(centroids__[points_to_clusters__[pid]],
					ps__->getPoint(pid));
			all_distances__[points_to_clusters__[pid]].insert(pid, min);
			// foreach centroid
			cid = 0;
			move = false;
			foreach(Centroids::value_type c, centroids__)
			{
				if(!all_distances__[cid].contains(pid))
					all_distances__[cid].insert(pid, cosinDist(c, ps__->getPoint(pid)));
				d = all_distances__[cid][pid];
				if (d < min)
				{
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
			if (move)
			{
				// insert
				points_to_clusters__[pid] = to_cluster;
				clusters_to_points__[to_cluster].insert(pid);
				//std::cout << "\t\tmove to cluster=" << to_cluster << std::endl;
			}
		}

		num_iterations++;
	} // end while (some_point_is_moving)
	if(store_states__)
		this->storeCurrentIterationState();
	used_iterations__ = num_iterations;
}


void KMeans::storeCurrentIterationState()
{
	int i=0;
	QString status;
	QTextStream stream(&status);
	foreach(const SetPoints set, clusters_to_points__)
	{
		stream << i << "(";
		foreach(Coord c, centroids__[i])
			stream << c << ", ";
		stream << "): ";
		QList<PointId> points = set.values();
		qSort(points.begin(), points.end());
		foreach(const PointId point, points)
			stream << point << ", ";
		stream << endl;
		++i;
	}
	stream << "Distances: " << endl;
	foreach(unsigned int cid, all_distances__.keys())
	{
		stream << cid << ":" << endl;
		foreach(unsigned int pid, all_distances__[cid].keys())
			stream << pid << ":" << all_distances__[cid][pid] << ", " << endl;
	}
	iterations_states__.push_back(status);
}

