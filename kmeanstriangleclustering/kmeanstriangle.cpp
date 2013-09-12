#include "kmeanstriangle.hpp"
#include "kmeanscomparer.h"
#include <limits>

KMeansTriangle::KMeansTriangle(ClusterId nclusters, unsigned int numIters, AbstractPointsSpace* ps, bool store) :
	KMeans(nclusters, numIters, ps, store),
	conditions_use_counter__(0),
	sVector__(nclusters, std::numeric_limits<Distance>::max()),
	centersToCenters__(nclusters, QVector<Distance>(nclusters, 0.0)),
	lowerBounds__(nclusters, QVector<Distance>(ps->getNumPoints(), 0.0)),
	upperBounds__(ps->getNumPoints(), std::numeric_limits<Distance>::max()),
	new_centroids__(nclusters, Point()),
	rVector__(ps->getNumPoints(), false)
{

}


void KMeansTriangle::compute_centroids(QTextStream& log)
{
	Dimensions i;
	ClusterId cid = 0;
	PointId num_points_in_cluster;
	// For each centroid
	for(int cid = 0; cid < centroids__.size(); ++cid)
	{
		num_points_in_cluster = 0;
		for(unsigned int crd = 0; crd < num_dimensions__; ++crd)
			new_centroids__[cid][crd] = 0;
		// For earch PointId in this set
		foreach(PointId pid, clusters_to_points__[cid])
		{
			Point p = ps__->getPoint(pid);
			for (i=0; i<num_dimensions__; i++)
				new_centroids__[cid][i] += p[i];
			num_points_in_cluster++;
		}
		// if no point in the clusters, this goes to inf (correct!)
		for (i=0; i<num_dimensions__; i++)
			new_centroids__[cid][i] /= num_points_in_cluster;
	}
}

void KMeansTriangle::assignDSVectors()
{
	for (unsigned int a = 0; a < centroids__.size() - 1; ++a)
	{
		centersToCenters__[a][a] = 0;
        for (int b = a + 1; b < centroids__.size(); ++b)
            centersToCenters__[a][b] = centersToCenters__[b][a] =
                    countDistance(centroids__[a], centroids__[b]);
	}
    for (int a = 0; a < centroids__.size(); ++a)
	{
//        if(a != 0)
//            sVector__[a] = centersToCenters__[a][0];
        for (unsigned int b = 0; b < centroids__.size(); ++b)
        {
            if(a == b)
                continue;
            if (sVector__[a] > centersToCenters__[a][b]/2.0)
                sVector__[a] = centersToCenters__[a][b]/2.0;
        }
	}
}

void KMeansTriangle::computeLowerAndUpperBounds()
{
	QVector<Distance> delta(this->num_clusters__);
	for (unsigned int cid = 0; cid < centroids__.size(); ++cid)
        delta[cid] = countDistance(centroids__[cid], new_centroids__[cid]);

	for (unsigned int pid = 0; pid < lowerBounds__.size(); ++pid)
	{
		for (unsigned int cid = 0; cid < centroids__.size(); ++cid)
		{
            lowerBounds__[pid][cid] = lowerBounds__[pid][cid] - delta[cid];
//                    fabs(lowerBounds__[pid][cid] - delta[cid]);
            if (lowerBounds__[pid][cid] < 0)
                lowerBounds__[pid][cid] = 0;
		}
		upperBounds__[pid] += delta[points_to_clusters__[pid]];
	}
}

bool KMeansTriangle::computePointsAssignements(QTextStream& log)
{
	bool change = false;
	bool move = false;
	ClusterId to_cluster = 0;
	Distance d, min;
	for (unsigned int pid = 0; pid < upperBounds__.size(); ++pid)
	{
		if (upperBounds__[pid] > sVector__[points_to_clusters__[pid]])
		{
			for (unsigned int a = 0; a < centroids__.size(); ++a)
			{
				log << pid << ':' << "upperBounds__[pid] < sVector__[" << points_to_clusters__[pid] << "]: " << (upperBounds__[pid] < sVector__[points_to_clusters__[pid]]) << endl;
				log << "upperBounds__[pid] > lowerBounds__[" << a << "][pid]: " << (upperBounds__[pid] > lowerBounds__[a][pid]) << endl;
				log << "upperBounds__[pid] > centersToCenters__[points_to_clusters__[pid]][a]/2.0: " << (upperBounds__[pid] > centersToCenters__[points_to_clusters__[pid]][a]/2.0) << endl << endl;
                if(upperBounds__[pid] < sVector__[a])
					continue;
				if (a != points_to_clusters__[pid] &&
                        upperBounds__[pid] < lowerBounds__[a][pid] &&
                        upperBounds__[pid] > centersToCenters__[points_to_clusters__[pid]][a]/2.0)
				{
					if (rVector__[pid])
					{
						if(!all_distances__[points_to_clusters__[pid]].contains(pid))
                            all_distances__[points_to_clusters__[pid]].insert(pid, countDistance(ps__->getPoint(pid),
																							 centroids__[points_to_clusters__[pid]]));
						min = all_distances__[points_to_clusters__[pid]][pid];
						rVector__[pid] = false;
					}
					else
						min = upperBounds__[pid];
					if(min > lowerBounds__[a][pid] || min > 0.5 * centersToCenters__[points_to_clusters__[pid]][a])
					{
						if(!all_distances__[a].contains(pid))
                            all_distances__[a].insert(pid, countDistance(ps__->getPoint(pid), centroids__[a]));
						d = all_distances__[a][pid];
                        if(d < min) // move
						{
							min = d;
							clusters_to_points__[points_to_clusters__[pid]].remove(pid);
							move = true;
							change = true;
							to_cluster = a;
						}
					}
				}
			} // all centers checked
			if(move)
			{
				log << pid << ':' << points_to_clusters__[pid] << '>' << to_cluster << endl;
				clusters_to_points__[to_cluster].insert(pid);
				points_to_clusters__[pid] = to_cluster;
				upperBounds__[pid] = lowerBounds__[to_cluster][pid];
				rVector__[pid] = false;
				move = false;
				++num_moved__;
			}
		}
	}
	return change;
}

void KMeansTriangle::initial_partition_points()
{
	ClusterId cid;
	for (PointId pid = 0; pid < ps__->getNumPoints(); pid++)
	{
		cid = pid % num_clusters__;
		points_to_clusters__.push_back(cid);
		clusters_to_points__[cid].insert(pid);
	}
}

/***
  * Method for executing k-means clustering algorithm with traingle inequality
  */
void KMeansTriangle::executeAlgorithm()
{
	QTextStream out(stdout);
	QFile log_file__("log_algh.txt");
	QTextStream* log_stream__;
	if(log_file__.open(QFile::WriteOnly))// | QFile::Append))
		log_stream__ = new QTextStream(&log_file__);
	else
		log_stream__ = new QTextStream(stdout);
	bool some_point_is_moving = true;
	unsigned int num_iterations = 0;
	PointId pid;
	ClusterId cid, to_cluster;
	Distance d, min;

	//
	// Initial partition of points
	//
	initial_partition_points();
    _algorithmPosition = InitialClusters;
    if(monitor__)
        monitor__->waitOnComparer();
	compute_centroids(*log_stream__);
	centroids__ = new_centroids__;
    assignDSVectors();
	if(store_states__)
		this->storeCurrentIterationState();
    _algorithmPosition = CentersComputed;
    if(monitor__)
        monitor__->waitOnComparer();

	firstLoop(*log_stream__);
    _algorithmPosition = DistancesCounted;
    if(monitor__)
        monitor__->waitOnComparer();

	compute_centroids(*log_stream__);
	this->computeLowerAndUpperBounds();
	this->rVector__ = QVector<bool>(ps__->getNumPoints(), true);

	if(store_states__)
		this->storeCurrentIterationState();
	num_iterations = 1;
	int skipped_1=0, skipped_2 = 0, skipped_3 = 0;
	for(int distIterator =0; distIterator < this->num_clusters__; ++distIterator)
		all_distances__[distIterator].clear();
	while (some_point_is_moving && num_iterations <= iterationsCount__)
	{
		for(int distIterator =0; distIterator < this->num_clusters__; ++distIterator)
			all_distances__[distIterator].clear();
		centroids__ = new_centroids__;
        _algorithmPosition = CentersComputed;
        if(monitor__)
            monitor__->waitOnComparer();
		some_point_is_moving = false;

		if(store_states__)
			this->storeCurrentIterationState();

		sVector__ = QVector<Distance>(this->num_clusters__, std::numeric_limits<Distance>::max());
		++num_iterations;

		this->assignDSVectors();

		some_point_is_moving = this->computePointsAssignements(*log_stream__);
        _algorithmPosition = DistancesCounted;
        if(monitor__)
            monitor__->waitOnComparer();
		compute_centroids((*log_stream__));
		this->computeLowerAndUpperBounds();
        if(store_states__)
            this->storeCurrentIterationState();
		rVector__ = QVector<bool>(ps__->getNumPoints(), true);
	} // end while (some_point_is_moving)
	used_iterations__ = num_iterations;
    _algorithmPosition = EndLoop;
    if(monitor__)
        monitor__->notifyAboutThreadEnd(this);
	if(store_states__)
		this->storeCurrentIterationState();
	(*log_stream__).flush();
	log_file__.close();
	delete log_stream__;
}

void KMeansTriangle::firstLoop(QTextStream& log)
{
	ClusterId to_cluster;
	Distance d, min;
	bool move = false;
	for(PointId pid = 0; pid < ps__->getNumPoints(); ++pid)
	{
        min = countDistance(centroids__[points_to_clusters__[pid]],
			ps__->getPoint(pid));
		lowerBounds__[points_to_clusters__[pid]][pid] = min;
		upperBounds__[pid] = min;
		for(ClusterId cid =0; cid < num_clusters__; ++cid)
		{
			if(cid != points_to_clusters__[pid])
			{
                d = countDistance(centroids__[cid], ps__->getPoint(pid));
				lowerBounds__[cid][pid] = d;
				if(d<min)
				{
					upperBounds__[pid] = d;
					move = true;
					min = d;
					to_cluster = cid;
				}
			}
		}
		if(move)
		{
			log << pid << ':' << points_to_clusters__[pid] << ':' << to_cluster << endl;
			move = false;
			clusters_to_points__[points_to_clusters__[pid]].remove(pid);
			points_to_clusters__[pid] = to_cluster;
			clusters_to_points__[to_cluster].insert(pid);
			++num_moved__;
		}
	}
    if(store_states__)
        this->storeCurrentIterationState();

}

void KMeansTriangle::initialLoop(QTextStream* log_stream__)
{
	PointId pid;
	ClusterId cid, to_cluster;
	Distance d, min;
	bool move = false;
	// for each point
	for (pid = 0; pid < num_points__; pid++)
	{
		rVector__[pid] = true;
		// distance from current cluster
        min = countDistance(centroids__[points_to_clusters__[pid]],
			ps__->getPoint(pid));
		all_distances__[points_to_clusters__[pid]].insert(pid, min);
//				pointsToCenters__[pid][points_to_clusters__[pid]] = min;
		this->upperBounds__[pid] = min;
		// foreach centroid
		cid = 0;
		move = false;
		for(int l=0; l<this->num_clusters__; ++l)
		{
			if(l == points_to_clusters__[pid])
				continue;
			Point c(this->centroids__[l]);
			if(centersToCenters__[points_to_clusters__[pid]][l] >= 2*min)
				d = min;
			else
			{
				if(!all_distances__[cid].contains(pid))
                    all_distances__[cid].insert(pid, countDistance(c, ps__->getPoint(pid)));
				d = all_distances__[cid][pid];
				(*log_stream__) << "pid: " << pid << " cid: " << l << " min: " << min << " d: " << d <<  " ? "  << (d<min)
								<< " conds : " << (centersToCenters__[points_to_clusters__[pid]][l] >= 2*min) << endl;
			}

			this->lowerBounds__[l][pid] = d;
			if (d < min)
			{
				min = d;
				move = true;
				to_cluster = cid;
				this->upperBounds__[pid] = min;
				// remove from current cluster
				clusters_to_points__[points_to_clusters__[pid]].remove(pid);
			}
			cid++;
		}
		if (move) {
			points_to_clusters__[pid] = to_cluster;
			clusters_to_points__[to_cluster].insert(pid);
//					std::cout << "\t\tmove to cluster=" << to_cluster << std::endl;
		}
	}
}

void KMeansTriangle::storeCurrentIterationState()
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









