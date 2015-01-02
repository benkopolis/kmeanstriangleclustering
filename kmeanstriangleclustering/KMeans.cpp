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
    foreach(PointId pid, pc.keys())
	{
        cout << "pid[" << pid << "]=" << pc[pid] << endl;
	}
	return os;
}

//////////////////////////////////////////////
//
//  K - MEANS
//
//////////////////////////////////////////////



KMeans::KMeans(ClusterId nclusters, unsigned int numIters,
               AbstractPointsSpace* ps) :
	iterationsCount__(numIters),
	ps__(ps),
	distances_call_count__(0),
    num_clusters__(nclusters),
    used_iterations__(0),
    num_moved__(0)
{
    //logall(KMeans::KMeans);
	ClusterId i = 0;
	Dimensions dim;
	num_dimensions__ = ps->getNumDimensions();
	num_points__ = ps->getNumPoints();
    for (; i < nclusters; i++) {
		Point point; // each centroid is a point
		for (dim = 0; dim < num_dimensions__; dim++)
			point.insert(i, 0.0);
        SetPoints* set_of_points = new SetPoints();

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
    logall("KMeans::~KMeans() ");
    monitor__ = 0;
    ps__ = 0;
    foreach(PointId p, points_distances__.keys())
    {
        delete points_distances__[p];
        points_distances__[p] = 0;
    }
    foreach(PointId p, distances_to_points__.keys())
    {
        delete distances_to_points__[p];
        distances_to_points__[p] = 0;
    }
    foreach(PointId p, temporary_groups__.keys())
    {
        delete temporary_groups__[p]->first;
        temporary_groups__[p]->first = 0;
        delete temporary_groups__[p];
        temporary_groups__[p] = 0;
    }
    logall("KMEANS DESTRIOYED");
}

//
// Zero centroids
//
void KMeans::zero_centroids() {

    logall("KMeans::zero_centroids()");
    for(int i=0; i<centroids__.size();++i)
    {
        foreach(unsigned int j, centroids__[i].keys())
        {
            centroids__[i][j] = 0.0;
        }
    }
}

//
// Compute Centroids
//
void KMeans::compute_centroids()
{
    logall("KMeans::compute_centroids()");
	Dimensions i;
	ClusterId cid = 0;
	PointId num_points_in_cluster;
	// For each centroid
    QVector<Point> means(centroids__.size(), QHash<unsigned int, Coord>());
    for(int i = 0; i< means.size(); ++i)
    {
        for(unsigned int j=0; j<ps__->getNumDimensions(); ++j)
            means[i].insert(j, 0);
    }
    foreach(Point centroid, centroids__)
	{
		num_points_in_cluster = 0;
		// For earch PointId in this set
        logall(QString("Center %1 has assigned points: ").arg(QString::number(cid)));
        foreach(PointId pid, *clusters_to_points__[cid])
		{
            const Point& p = ps__->getPoint(pid);
			for (i=0; i<num_dimensions__; i++)
				means[cid][i] += p[i];
			num_points_in_cluster++;
            logoneline(QString("%1, ").arg(QString::number(pid)));
		}
		//
		// if no point in the clusters, this goes to inf (correct!)
		//
        logall(QString("Center %1 has coords: ").arg(QString::number(cid)));
		for (i=0; i<num_dimensions__; i++)
        {
			means[cid][i] /= num_points_in_cluster;
            logoneline(QString("%1:%2, ").arg(QString::number(i), QString::number(means[cid][i])));
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
    logall("KMeans::initial_partition_points()");
    if(_initial_partition_type == Sequential)
        sequential_partition_points();
    else if(_initial_partition_type == MinimalNumberOfDimensions)
        minimal_dimensions_partitions_points();
    else if(_initial_partition_type == DeterminigNumberOfClusters)
        determinig_number_of_clusters_partition_points();
}

void KMeans::sequential_partition_points()
{
    logall("KMeans::sequential_partition_points()");
}

void KMeans::fillPointsDistances()
{
    logall("KMeans::fillPointsDistances()");
    Distance tmp = 0.0;
    for(PointId pi=0; pi < ps__->getNumPoints()-1; ++pi)
    {
        points_distances__.insert(pi, new QHash<PointId, Distance>());
        distances_to_points__.insert(pi, new QMultiMap<Distance, PointId>());
        if(pi > 0)
        {
            for(int ri=pi-1; ri>=0;--ri)
                distances_to_points__[pi]->insert(distances_to_points__[(unsigned)ri]->value(pi),
                                                  (unsigned)ri);
        }
        for(PointId qi=pi+1; qi < ps__->getNumPoints(); ++qi)
        {
            tmp = hammingSimplified(ps__->getPoint(pi), ps__->getPoint(qi));
            points_distances__[pi]->insert(qi, tmp);
            //sorted_edges__.insert(tmp, new QPair<PointId, PointId>(pi, qi));
            distances_to_points__[pi]->insert(tmp, qi);
        }
    }
    unsigned int lastPoint = ps__->getNumPoints() -1;
    distances_to_points__.insert(lastPoint, new QMultiMap<Distance, PointId>());
    for(int ri= lastPoint-1; ri>=0;--ri)
        distances_to_points__[lastPoint]->insert(distances_to_points__[(unsigned)ri]->value(lastPoint),
                                          (unsigned)ri);
}

void KMeans::minimal_dimensions_partitions_points()
{
    logall("KMeans::minimal_dimensions_partitions_points()");
    fillPointsDistances();
    QSet<PointId> *usedPoints = new QSet<PointId>();
    int low=0, high = ps__->getNumPoints() / num_clusters__;
    int pDelta = high;
    QVector<QList<PointId>*> pointsForCheck(this->num_clusters__, 0);
    QSet<PointId>* notUsedPoints = new QSet<PointId>();
    for(PointId pi=0; pi < ps__->getNumPoints()-1; ++pi)
        notUsedPoints->insert(pi);
    for(unsigned int j=0; j < num_clusters__; ++j) // think about better way to choose seeds
    {
        PointId seed = qrand() % ((high + 1) - low) + low;
        QPair<QSet<PointId>*, Distance>* pair =
                new QPair<QSet<PointId>*, Distance>(new QSet<PointId>(), 0);
        pair->first->insert(seed);
        usedPoints->insert(seed);
        temporary_groups__.insert(j, pair);
        pointsForCheck[j] = new QList<PointId>();
        *pointsForCheck[j] << seed;
        low += pDelta;
        high += pDelta;
    } // now groups are initialized with two points each
    PointId groupId = 0;
    int usedPointsSize = 0;
    QList<PointId> * newPointsToCheck = 0;
    while((unsigned)usedPoints->size() < ps__->getNumPoints())
    {
        if(!(groupId < num_clusters__))
            groupId = 0;
        usedPointsSize = usedPoints->size();
        newPointsToCheck =
                iterateOverTemporaryGroupsAndAssignPoints(groupId,
                                                          usedPoints,
                                                          notUsedPoints,
                                                          pointsForCheck[groupId]);
        delete pointsForCheck[groupId];
        pointsForCheck[groupId] = newPointsToCheck;
        ++groupId;
    }
    delete usedPoints;
    usedPoints = 0;
    delete notUsedPoints;
    notUsedPoints = 0;
    for(unsigned int j=0; j<this->num_clusters__; ++j)
    {
        delete pointsForCheck[j];
        pointsForCheck[j] = 0;
    }
}

QList<PointId> * KMeans::iterateOverTemporaryGroupsAndAssignPoints(PointId groupId,
                                                                   QSet<PointId> *usedPoints,
                                                                   QSet<PointId> *notUsedPoints,
                                                                   QList<PointId>* pointsToCheck)
{
    logall("KMeans::iterateOverTemporaryGroupsAndAssignPoints");
    QList<PointId> * result = new QList<PointId>();
    foreach(PointId pointInGroup, *pointsToCheck)
    { // first the greedy version
        if(distances_to_points__.contains(pointInGroup))
        {
            Distance minK = distances_to_points__[pointInGroup]->begin().key();
            QList<QPair<Distance, PointId> > toRemoveFromDists;
            foreach(PointId newP, distances_to_points__[pointInGroup]->values(minK))
            {
                if(!usedPoints->contains(newP))
                {
                    usedPoints->insert(newP);
                    *result << newP;
                    temporary_groups__[groupId]->first->insert(newP);
                    temporary_groups__[groupId]->second += getWeightOfConnecting(newP,
                                temporary_groups__[groupId]->first);
                    notUsedPoints->remove(newP);
                }
                else
                    toRemoveFromDists << QPair<Distance, PointId>(minK, newP);
            }
            QPair<Distance, PointId> p;
            foreach(p, toRemoveFromDists)
                distances_to_points__[pointInGroup]->remove(p.first, p.second);
            if(distances_to_points__[pointInGroup]->size() == 0)
            {
                delete distances_to_points__[pointInGroup];
                distances_to_points__[pointInGroup] = 0;
                distances_to_points__.remove(pointInGroup);
            }
        }
    }

    return result;
}

Distance KMeans::getWeightOfConnecting(PointId p, const QSet<PointId>* set) const
{
    logall("KMeans::getWeightOfConnecting(PointId p, const QSet<PointId>* set)");
    Distance weight = 0.0;
    foreach(PointId q, *set)
        weight += get_dist_p2p(p, q);
    return weight;
}

Distance KMeans::get_dist_p2p(PointId x, PointId y) const
{
    logall("KMeans::get_dist_p2p(PointId x, PointId y)");
    if (x == y)
        return 0.0;
    else if(points_distances__.contains(x) && points_distances__[x]->contains(y))
        return (*points_distances__[x])[y];
    else if(points_distances__.contains(y) && points_distances__[y]->contains(x))
        return (*points_distances__[y])[x];
    else
    {
        Distance tmp = hammingSimplified(ps__->getPoint(x), ps__->getPoint(y));
        if (x < y && points_distances__.contains(x))
            points_distances__[x]->insert(y, tmp);
        else if (y < x && points_distances__.contains(y))
            points_distances__[y]->insert(x, tmp);
        return tmp;
    }
}

int KMeans::getTemporaryGroupsSize() const
{
    logall("KMeans::getTemporaryGroupsSize()");
    int size = 0;
    QPair<QSet<PointId>*, Distance>* group;
    foreach(group, temporary_groups__.values())
        size += group->first->size();
    return size;
}

void KMeans::determinig_number_of_clusters_partition_points()
{
    logall("KMeans::determinig_number_of_clusters_partition_points()");
    if(dimensions_delta__ == 0)
        return;
    fillPointsDistances();
}

QSet<PointId> KMeans::getUniqueUnion(const QList<PointId>& one, const QList<PointId>& two) const
{
    logall("KMeans::getUniqueUnion(const QList<PointId>& one, const QList<PointId>& two)");
    return one.toSet() + two.toSet();
}

Distance KMeans::countDistance(const Point& p, const Point& q) const
{
    logall("KMeans::countDistance(const Point& p, const Point& q)");
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

Distance KMeans::dotMatrixes(const Point& a, const Point& b) const
{
    logall("KMeans::dotMatrixes(const Point& a, const Point& b) const");
    Distance result = 0;
    foreach (Coord c, a) {
        foreach (Coord i, b)
            result = result + c * i;
    }
    return result;
}

Distance KMeans::euclideanDistance(const Point& p, const Point& q) const
{
    logall("KMeans::euclideanDistance(const Point& p, const Point& q) const");
    long double sigma = 0.0;
    int a = p.size();
    int b = q.size();
    const QSet<PointId>& uniqueUnion = b == 0 ? (a == 0 ? QSet<PointId>() : q.keys().toSet()) :
                                                 (a == 0 ? p.keys().toSet() : getUniqueUnion(p.keys(), q.keys()));
    foreach(PointId i, uniqueUnion)
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

Distance KMeans::hammingDistance(const Point& p, const Point& q) const
{
    logall("KMeans::hammingDistance(const Point& p, const Point& q) const");
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

Distance KMeans::hammingSimplified(const Point& p, const Point& q) const
{
    logall("KMeans::hammingSimplified(const Point& p, const Point& q) const");
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

Distance KMeans::cosineDistance(const Point& p, const Point& q) const
{
    logall("KMeans::cosineDistance(const Point& p, const Point& q) const");
    return 1.0 - (dotMatrixes(p, q) / sqrt(dotMatrixes(p, p))
                * sqrt(dotMatrixes(q, q)));
}

/**
  *
  */
void KMeans::move_point(PointId pid, ClusterId to_cluster)
{
    logall("KMeans::move_point(PointId pid, ClusterId to_cluster, bool* move)");
    clusters_to_points__[points_to_clusters__[pid]]->remove(pid);
    // insert
    points_to_clusters__[pid] = to_cluster;
    clusters_to_points__[to_cluster]->insert(pid);
    logall(QString("Moving point %1 to center %2").arg(QString::number(pid), QString::number(to_cluster)));
}

void KMeans::executeAlgorithm()
{
    logall("KMeans::executeAlgorithm()");
    bool move=false;
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
    logall("Before firs loop - preprocessing");

    initial_partition_points();

    while (some_point_is_moving && num_iterations < iterationsCount__)
    {
        logall(QString("Iteration %1").arg(num_iterations));
		some_point_is_moving = false;
        compute_centroids();
        all_distances__.clear();
		// for each point
		for (pid = 0; pid < num_points__; pid++)
		{
			// distance from current cluster
            min = countDistance(centroids__[points_to_clusters__[pid]],
					ps__->getPoint(pid));
            logall(QString("Point %1 assigned to %2 with distance %3").arg(QString::number(pid),
                                                                           QString::number(points_to_clusters__[pid]),
                                                                           QString::number(min)));
			// foreach centroid
            for(ClusterId cid=0; cid <  (unsigned)centroids__.size(); ++cid)
			{
				if(cid != points_to_clusters__[pid])
				{
                    d = countDistance(centroids__[cid], ps__->getPoint(pid));
                    all_distances__[cid].insert(pid, d);
                    logall(QString("Point %1 to center %2 has distance %3 ").arg(QString::number(pid),
                                                                                QString::number(cid),
                                                                                QString::number(d)));
					if (d < min)
					{
						min = d;
						move = true;
						to_cluster = cid;
						++num_moved__;
						some_point_is_moving = true;
                        logall(QString("Point %1 will be moved to center %2").arg(QString::number(pid), QString::number(cid)));
					}
				}
			}
			if (move)
                move_point(pid, to_cluster);
            move = false;
		}
		num_iterations++;
	} // end while (some_point_is_moving)
	used_iterations__ = num_iterations;
	(*log_stream__) << endl << endl << endl;
	log_stream__->flush();
	log_file__.close();
	delete log_stream__;
}


void KMeans::storeCurrentIterationState()
{
    logall("KMeans::storeCurrentIterationState()");
	int i=0;
	QString status;
	QTextStream stream(&status);
    foreach(const SetPoints* set, clusters_to_points__)
	{
		stream << i << "(";
		foreach(Coord c, centroids__[i])
			stream << c << ", ";
		stream << "): ";
        QList<PointId> points = set->values();
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

void KMeans::printIterationStates(QTextStream& log)
{
    logall("KMeans::printIterationStates(QTextStream& log)");
    foreach(QString status, this->iterations_states__)
        log << status << endl;
}

Distance KMeans::meanSquareError()
{
    logall("KMeans::meanSquareError()");
	Distance mean = 0.0;
//	QTextStream out(stdout);
	QVector<Distance> lens(ps__->getNumPoints());
    for(unsigned int i=0; i<this->ps__->getNumPoints(); ++i)
	{
        lens[i] = countDistance(ps__->getPoint(i), centroids__[points_to_clusters__[i]]);
		mean += lens[i];
	}
	mean /= ps__->getNumPoints();
//	out << "Mean: " << mean << endl;
	Distance error = 0.0;
    for(unsigned int i=0; i<this->ps__->getNumPoints(); ++i)
		error += (lens[i] - mean)*(lens[i] - mean);
	error /= (double)(ps__->getNumPoints()*(ps__->getNumPoints() - 1));
//	out << "Error: " << error << endl;
	return sqrt(error);
}



