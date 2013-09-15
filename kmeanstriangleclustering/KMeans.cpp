/*
 * KMeans.cpp
 *
 *  Created on: 12-12-2012
 *      Author: zby
 */

#include "KMeans.hpp"
#include "models.hpp"
#include "kmeanscomparer.h"
#include "commons/sequentialcenterspicker.h"

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
	foreach(PointsToClusters::value_type cid, pc)
	{
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


KMeans::KMeans(ClusterId nclusters, unsigned int numIters,
               AbstractPointsSpace* ps, bool store,
               KMeansComparer *monitor) :
    _algorithmPosition(None),
	iterationsCount__(numIters),
	ps__(ps),
	distances_call_count__(0),
    num_clusters__(nclusters),
	used_iterations__(0),
	store_states__(store),
	num_moved__(0),
    distance_type__(Euclidean),
    monitor__(monitor),
    _initial_partition_type(Sequential)
{
	ClusterId i = 0;
	Dimensions dim;
	num_dimensions__ = ps->getNumDimensions();
	num_points__ = ps->getNumPoints();
    if(monitor__ != 0)
        monitor__->addAlgorithm(this);
	for (; i < nclusters; i++) {
		Point point; // each centroid is a point
		for (dim = 0; dim < num_dimensions__; dim++)
			point.insert(i, 0.0);
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
    monitor__ = 0;
    ps__ = 0;
}


void KMeans::countPreRandIndex()
{
	for(PointId i=0; i < ps__->getNumPoints()-1; ++i)
	{
		int tmp = ps__->getNumPoints()-1;
        if(points_to_clusters__[i] == points_to_clusters__[tmp])
            pre_rand_index__[QPair<PointId, PointId>(i, tmp)] = true;
        for(PointId j= i+1; j < ps__->getNumPoints()-1; ++j)
            if(points_to_clusters__[i] == points_to_clusters__[j])
                pre_rand_index__[QPair<PointId, PointId>(i, j)] = true;
	}
}

bool KMeans::storePreRandIndex(QString fileName) const
{
	QFile file(fileName);
    if(pre_rand_index__.size() == 0)
        return false;
	if(!file.open(QFile::WriteOnly))
		return false;
	QTextStream out(&file);
	out << ps__->getNumPoints() << ' ' << num_clusters__ << ' ' << ps__->getNumPoints() << endl;
    QPair<PointId, PointId> p;
    foreach(p, pre_rand_index__.keys())
        out << p.first << ':' << p.second << endl; // write only those pairs that are in the same cluster - rest is in different clusters
    out.flush();
    file.close();
	return true;
}

void KMeans::printClustersSize(QTextStream& stream) const
{
	for(ClusterId i=0; i < num_clusters__; ++i)
		stream << i << ": " << clusters_to_points__[i].size() << endl;
}

//
// Zero centroids
//
void KMeans::zero_centroids() {

	foreach(Point centroid, centroids__)
	{
		foreach(Coord d, centroid)
		{
			d = 0.0;
		}
	}
}

//
// Compute Centroids
//
void KMeans::compute_centroids()
{
	Dimensions i;
	ClusterId cid = 0;
	PointId num_points_in_cluster;
	// For each centroid
    QVector<Point> means(centroids__.size(), QHash<unsigned int, Coord>());
    for(int i = 0; i< means.size(); ++i)
    {
        for(int j=0; j<ps__->getNumDimensions(); ++j)
            means[i].insert(j, 0);
    }
    foreach(Point centroid, centroids__)
	{
		num_points_in_cluster = 0;
		// For earch PointId in this set
		foreach(PointId pid, clusters_to_points__[cid])
		{
			Point p = ps__->getPoint(pid);
			for (i=0; i<num_dimensions__; i++)
				means[cid][i] += p[i];
			num_points_in_cluster++;
		}
		//
		// if no point in the clusters, this goes to inf (correct!)
		//
		for (i=0; i<num_dimensions__; i++)
			means[cid][i] /= num_points_in_cluster;
		cid++;
	}
	centroids__ = means;
}

void KMeans::testInitialPartitioning(InitialPartitionType type)
{
    InitialPartitionType old = _initial_partition_type;
    this->setInitialPartitionType(type);
    this->initial_partition_points();
    this->setInitialPartitionType(old);
}

//
// Initial partition points among available clusters
//
void KMeans::initial_partition_points()
{
    if(_initial_partition_type == Sequential)
        sequential_partition_points();
    else if(_initial_partition_type == MinimalNumberOfDimensions)
        minimal_dimensions_partitions_points();
    else if(_initial_partition_type == DeterminigNumberOfClusters)
        determinig_number_of_clusters_partition_points();
}

void KMeans::sequential_partition_points()
{
    ClusterId cid;
    for (PointId pid = 0; pid < ps__->getNumPoints(); pid++)
    {
        cid = pid % num_clusters__;
        points_to_clusters__.push_back(cid);
        clusters_to_points__[cid].insert(pid);
    }
}

void KMeans::fillPointsDistances()
{
    Distance tmp = 0.0;
    for(PointId pi=0; pi < ps__->getNumPoints()-1; ++pi)
    {
        points_distances__.push_back(QList<Distance>());
        for(PointId qi=pi+1; qi < ps__->getNumPoints(); ++qi)
        {
            tmp = hammingSimplified(ps__->getPoint(pi), ps__->getPoint(qi));
            points_distances__[pi].push_back(tmp);
            sorted_edges__.insert(tmp, QPair<PointId, PointId>(pi, qi));
        }
    }
}

void KMeans::minimal_dimensions_partitions_points()
{
    fillPointsDistances();
    QList<QPair<PointId, PointId> > possibleSeeds;
    QListIterator<Distance> i(sorted_edges__.uniqueKeys());
    int seedsCount = num_clusters__*10;
    while(possibleSeeds.size() < seedsCount && i.hasNext())
    {
        Distance d = i.next();
        possibleSeeds.append(sorted_edges__.values(d));
    } // now possibleSeeds contains list of smallest edges, ready to perform draw
    QSet<PointId> *drawedPoints = new QSet<PointId>();
    for(int j=0; j < num_clusters__;) // think about better way to choose seeds
    {
        QPair<PointId, PointId> p = possibleSeeds.at(qrand() % possibleSeeds.size());
        if(drawedPoints->contains(p.first) || drawedPoints->contains(p.second))
            continue;
        drawedPoints->insert(p.first);
        drawedPoints->insert(p.second);
        QPair<QSet<PointId>, Distance> tmp;
        tmp.first.insert(p.first);
        tmp.first.insert(p.second);
        tmp.second = points_distances__[p.first][p.second];
        temporary_groups__.push_back(tmp);
        sorted_edges__.remove(points_distances__[p.first][p.second], p);
        ++j;
    } // now groups are initialized with two points each
    delete drawedPoints;
    drawedPoints = 0;
    QListIterator<QPair<QSet<PointId>, Distance> > l(temporary_groups__);
    while((PointId)getTemporaryGroupsSize() < ps__->getNumPoints())
    {
        if(!l.hasNext())
            l.toFront();
        QPair<QSet<PointId>, Distance> group = l.next();
        QListIterator<Distance> k(sorted_edges__.uniqueKeys());
        QMap<Distance, QPair<PointId, PointId> > possibleMatches;
        while(k.hasNext())
        {
            QPair<PointId, PointId> edge;
            foreach(edge, sorted_edges__.values(k.peekNext()))
            {
                if(group.first.contains(edge.first) && !group.first.contains(edge.second))
                    possibleMatches.insert(getWeightOfConnecting(edge.second, group.first),
                                           edge);
                else if(group.first.contains(edge.second) && !group.first.contains(edge.first))
                    possibleMatches.insert(getWeightOfConnecting(edge.first, group.first),
                                           edge);
            }
            if(possibleMatches.size() == 0)
                k.next();
            else
            {
                Distance toAdd = possibleMatches.uniqueKeys().first();
                QPair<PointId, PointId> adding = possibleMatches.values(toAdd).first();
                if(group.first.contains(adding.first))
                    group.first.insert(adding.second);
                else
                    group.first.insert(adding.first);
                sorted_edges__.remove(points_distances__[adding.first][adding.second], adding);
                group.second += toAdd;
            }
        }
    }
}

Distance KMeans::getWeightOfConnecting(PointId p, QSet<PointId> set)
{
    Distance weight = 0.0;
    foreach(PointId q, set)
        weight += points_distances__[p < q ? p : q][p < q ? q : p];
    return weight;
}

int KMeans::getTemporaryGroupsSize()
{
    int size = 0;
    QPair<QSet<PointId>, Distance> group;
    foreach(group, temporary_groups__)
        size += group.first.size();
    return size;
}

void KMeans::determinig_number_of_clusters_partition_points()
{
    fillPointsDistances();
}

QSet<PointId> KMeans::getUniqueUnion(QList<PointId> one, QList<PointId> two)
{
    return one.toSet() + two.toSet();
}

Distance KMeans::countDistance(const Point& p, const Point& q)
{
    ++distances_call_count__;

    if(distance_type__ == Hamming)
        return hammingDistance(p, q);
    else if(distance_type__ == Euclidean)
        return euclideanDistance(p, q);
    else if(distance_type__ == Cosin)
        return cosineDistance(p, q);
    else if(distance_type__ == HammingSimplified)
        return hammingSimplified(p, q);
    else
    {
        --distances_call_count__;
        return 0.0;
    }
}

Distance KMeans::dotMatrixes(const Point& a, const Point& b)
{
    Distance result = 0;
    foreach (Coord c, a) {
        foreach (Coord i, b)
            result = result + c * i;
    }
    return result;
}

Distance KMeans::euclideanDistance(const Point& p, const Point& q)
{
    long double sigma = 0.0;
    foreach(PointId i, getUniqueUnion(p.keys(), q.keys()))
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

Distance KMeans::hammingDistance(const Point& p, const Point& q)
{
    long double sigma = 0.0;
    foreach(PointId i, getUniqueUnion(p.keys(), q.keys()))
    {
        if(p.contains(i) && q.contains(i))
            sigma += fabs(p[i] - q[i]);
        else if(p.contains(i))
            sigma += p[i];
        else if(q.contains(i))
            sigma += q[i];
    }
    return sigma;
}

Distance KMeans::hammingSimplified(const Point& p, const Point& q)
{
    long double sigma = 0.0;
    foreach(PointId i, getUniqueUnion(p.keys(), q.keys()))
    {
        if(p.contains(i) && !q.contains(i))
            sigma += 1.0;
        else if(!p.contains(i) && q.contains(i))
            sigma += 1.0;
    }
    return sigma;
}

Distance KMeans::cosineDistance(const Point& p, const Point& q)
{
    return 1.0 - (dotMatrixes(p, q) / sqrt(dotMatrixes(p, p))
                * sqrt(dotMatrixes(q, q)));
}

void KMeans::run()
{
    executeAlgorithm();
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
	ClusterId to_cluster;
	Distance d, min;
	QString logName = "log_template.txt";
	if(distance_type__ != Euclidean)
		logName = "log_nottemp.txt";
	QFile log_file__(logName);
	QTextStream* log_stream__;
	if(log_file__.open(QFile::WriteOnly))// | QFile::Append))
		log_stream__ = new QTextStream(&log_file__);
	else
		log_stream__ = new QTextStream(stdout);
	//
	// Initial partition of points
    //
	initial_partition_points();
    _algorithmPosition = InitialClusters;
    if(monitor__)
        monitor__->waitOnComparer();
	//
	// Until not converge
	//
    while (some_point_is_moving && num_iterations < iterationsCount__)
	{
		some_point_is_moving = false;
        compute_centroids();
        _algorithmPosition = CentersComputed;
        if(monitor__)
            monitor__->waitOnComparer();
		if(store_states__)
			this->storeCurrentIterationState();
        all_distances__.clear();
		// for each point
		for (pid = 0; pid < num_points__; pid++)
		{
			// distance from current cluster
            min = countDistance(centroids__[points_to_clusters__[pid]],
					ps__->getPoint(pid));
			// foreach centroid
			move = false;
			for(ClusterId cid=0; cid <  centroids__.size(); ++cid)
			{
				if(cid != points_to_clusters__[pid])
				{
                    d = countDistance(centroids__[cid], ps__->getPoint(pid));
                    all_distances__[cid].insert(pid, d);
					if (d < min)
					{
						min = d;
						move = true;
						to_cluster = cid;
						++num_moved__;
						some_point_is_moving = true;
					}
				}
			}
			if (move)
			{
				(*log_stream__) << pid << ':' << points_to_clusters__[pid] << ':' << to_cluster << endl;
				clusters_to_points__[points_to_clusters__[pid]].remove(pid);
				// insert
				points_to_clusters__[pid] = to_cluster;
				clusters_to_points__[to_cluster].insert(pid);
			}
		}
        _algorithmPosition = DistancesCounted;
        if(monitor__)
            monitor__->waitOnComparer();
		num_iterations++;
	} // end while (some_point_is_moving)
    _algorithmPosition = EndLoop;
    if(monitor__)
        monitor__->notifyAboutThreadEnd(this);
	if(store_states__)
		this->storeCurrentIterationState();
	used_iterations__ = num_iterations;
	(*log_stream__) << endl << endl << endl;
	log_stream__->flush();
	log_file__.close();
	delete log_stream__;
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
    stream.flush();
	iterations_states__.push_back(status);
}

bool KMeans::printClusteringResults(QString fileName) const
{
    QFile file(fileName);
    if(!file.open(QFile::WriteOnly))
        return false;
    QTextStream stream(&file);
    int i=0;
    stream << num_clusters__ << ' ' << ps__->getNumPoints() << endl; // magic switch ;)
    foreach(const SetPoints set, clusters_to_points__)
    {
        foreach(const PointId point, set)
        {
            stream << point << ':' << "1.0" << ' ';
        }
        stream << endl;
        ++i;
    }
    stream.flush();
    file.close();
    return true;
}


void KMeans::printClusters(QTextStream& stream) const
{
    int i=0;
    foreach(const SetPoints set, clusters_to_points__)
    {
        stream << i << ':';
        foreach(const PointId point, set)
        {
            stream << point << ',';
        }
        stream << endl;
        ++i;
    }
}

void KMeans::printIterationStates(QTextStream& log)
{
    foreach(QString status, this->iterations_states__)
        log << status << endl;
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

bool KMeans::fillWithResults(QString fileName)
{
    QFile file(fileName);
    if(!file.open(QFile::ReadOnly))
        return false;
    QTextStream in(&file);
    int nClusters=0, nDims = 0;
    in >> nClusters >> nDims;
    int pIndex=0, cIndex=0;
    float coord=0.0;
    char c;
    while(!in.atEnd())
    {
        QString line = in.readLine();
        QTextStream inner(&line);
        while(!inner.atEnd())
        {
            inner >> pIndex >> c >> coord;
            points_to_clusters__[pIndex] = cIndex;
            clusters_to_points__[cIndex].insert(pIndex);
        }
        ++cIndex;
    }
    compute_centroids();
    file.close();
    return true;
}

Distance KMeans::meanSquareError()
{
	Distance mean = 0.0;
//	QTextStream out(stdout);
	QVector<Distance> lens(ps__->getNumPoints());
	for(int i=0; i<this->ps__->getNumPoints(); ++i)
	{
        lens[i] = countDistance(ps__->getPoint(i), centroids__[points_to_clusters__[i]]);
		mean += lens[i];
	}
	mean /= ps__->getNumPoints();
//	out << "Mean: " << mean << endl;
	Distance error = 0.0;
	for(int i=0; i<this->ps__->getNumPoints(); ++i)
		error += (lens[i] - mean)*(lens[i] - mean);
	error /= (double)(ps__->getNumPoints()*(ps__->getNumPoints() - 1));
//	out << "Error: " << error << endl;
	return sqrt(error);
}




