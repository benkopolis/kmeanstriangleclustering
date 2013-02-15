#include "kmeanstriangle.hpp"

KMeansTriangle::KMeansTriangle(ClusterId nclusters, unsigned int numIters, AbstractPointsSpace* ps, bool store) :
	KMeans(nclusters, numIters, ps, store), conditions_use_counter__(0)
//	    ,pointsToCenters__(nclusters, QVector<Distance>(ps.getNumPoints(), 1.0))
{

}


void KMeansTriangle::compute_centroids(bool first, QTextStream& log)
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
	for(int i=0; i < this->num_clusters__; ++i)
	{
		for(int j=0; j<this->num_clusters__; ++j)
		{
			if(j!=i)
			{
				this->centersToCenters__[i][j] =
						cosinDist(means[i], means[j]);
				double tmpDbg = 0.5 * centersToCenters__[i][j];
				sVector__[j] = tmpDbg;
			}
		}
		if(!first)
		{
			Distance delta =  cosinDist(centroids__[i], means[i]);
			for(int pid=0; pid<num_points__; ++pid)
			{
				Distance newLower = lowerBounds__[i][pid] - delta;
				lowerBounds__[i][pid] = newLower > 0 ? newLower : 0;
			}
		}
	}
	if(!first)
	{
		for(int pid=0; pid<num_points__; ++pid)
		{
			Distance delta =  cosinDist(centroids__[points_to_clusters__[pid]],
										means[points_to_clusters__[pid]]);
			upperBounds__[pid] = upperBounds__[pid] + delta;
			rVector__[pid] = true;
		}
	}
		centroids__ = means;
}

void KMeansTriangle::initial_partition_points()
{
	ClusterId cid;
	for(int i=0; i < this->num_clusters__; ++i)
	{
		sVector__.push_back(0);
		this->centersToCenters__.push_back(QVector<Distance>());
		this->lowerBounds__.push_back(QVector<Distance>());
		for(int j=0; j<this->num_clusters__; ++j)
			this->centersToCenters__[i].push_back(
					cosinDist(this->centroids__[i], this->centroids__[j]));
		for(int j=0; j<this->num_points__; ++j)
			this->lowerBounds__[i].push_back(0);
	}
	for (PointId pid = 0; pid < ps__->getNumPoints(); pid++) {

		rVector__.push_back(false);
		cid = pid % num_clusters__;
	//	std::cout << points_to_clusters__.size() << '\n';
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
	if(store_states__)
		this->storeCurrentIterationState();

	compute_centroids(true, *log_stream__);
	initialLoop(log_stream__);
	if(store_states__)
		this->storeCurrentIterationState();
	num_iterations = 1;
	int skipped_1=0, skipped_2 = 0, skipped_3 = 0;
	while (some_point_is_moving && num_iterations <= iterationsCount__)
	{
		if(store_states__)
			this->storeCurrentIterationState();
		some_point_is_moving = false;
		compute_centroids(false, *log_stream__); // also computes sVector and centersTocenters

		// foreach center
		for(cid =0; cid<num_clusters__; ++cid)
		{	// foreach point
			int dupiasta =20;
			for(pid =0; pid < num_points__; ++pid)
			{
				++conditions_use_counter__;
				(*log_stream__) << "ITER FOR cid:" << cid << " pid:" << pid << endl;
				if(pid ==8 && cid ==1)
					dupiasta = 2343;
				if(cid == points_to_clusters__[pid])
					continue;
				if(upperBounds__[pid] <= lowerBounds__[cid][pid])
				{
					(*log_stream__) << "skipped becouse: upperBounds__[" << pid << "] <= lowerBounds__[cid:"
									<< cid << "][pid:"
									<< pid << "]" << endl;
					++skipped_1;
					continue;
				}
				if(upperBounds__[pid] <=
						0.5*centersToCenters__[points_to_clusters__[pid]][cid])
				{
					(*log_stream__) << "skipped becouse: upperBounds__[" << pid << "] <= 0.5*centersToCenters__[points_to_clusters__[pid:"
									<< pid << "][cid:"
									<< cid << "]" << endl;
					++skipped_2;
					continue;
				}
				if(upperBounds__[pid] < sVector__[points_to_clusters__[pid]])
				{
					(*log_stream__) << "skipped becouse: upperBounds__[" << pid << "] < sVector__[points_to_clusters__[pid:"
									<< pid << "]]" << endl;
					++skipped_3;
					continue;
				}
				if(rVector__[pid])
				{
					if(!all_distances__[cid].contains(pid))
						all_distances__[cid].insert(pid, cosinDist(centroids__[cid], ps__->getPoint(pid)));
					rVector__[pid] = false;
				}
				else
					all_distances__[cid].insert(pid, upperBounds__[pid]);
				d = all_distances__[cid][pid];
				if(pid == 8) // todo debug
				{
					(*log_stream__) << "AAAA cid:" << cid << " d:" << cosinDist(centroids__[1], ps__->getPoint(pid))
									<< " cid:0 " << cosinDist(centroids__[0], ps__->getPoint(pid)) << endl;
					(*log_stream__) << "BBB pid:8(" << ps__->getPoint(8)[0] << ", " << ps__->getPoint(8)[1] << ')' << endl;
				}
				if(d > lowerBounds__[points_to_clusters__[pid]][pid]
						|| d > 0.5*centersToCenters__[points_to_clusters__[pid]][cid])
					{
						--conditions_use_counter__;
					if(!all_distances__[points_to_clusters__[pid]].contains(pid))
						all_distances__[points_to_clusters__[pid]].insert(pid,
							cosinDist(centroids__[points_to_clusters__[pid]], ps__->getPoint(pid)));
					Distance tmp = all_distances__[points_to_clusters__[pid]][pid];
					if(tmp > d) // move
					{
						(*log_stream__) << "TO MOVE (" << tmp << " < " << d << ") pid: " << pid << "cid: " << cid << endl;
						clusters_to_points__[points_to_clusters__[pid]].remove(pid); // remove from old cluster
						points_to_clusters__[pid] = cid;
						clusters_to_points__[cid].insert(pid);
						some_point_is_moving = true;
//							std::cout << "\t\tmove to cluster=" << to_cluster << std::endl;
					}
				}
			}
		}
		num_iterations++;
	} // end while (some_point_is_moving)
	used_iterations__ = num_iterations;
	if(store_states__)
		this->storeCurrentIterationState();
	(*log_stream__) << "Skipping becouse of 1 (" << skipped_1 << "), 2 (" << skipped_2 << "), 3 (" << skipped_3 << ")" << endl;
	(*log_stream__).flush();
	log_file__.close();
	delete log_stream__;
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
		min = cosinDist(centroids__[points_to_clusters__[pid]],
			ps__->getPoint(pid));
		all_distances__[points_to_clusters__[pid]].insert(pid, min);
//				pointsToCenters__[pid][points_to_clusters__[pid]] = min;
		this->upperBounds__.push_back(min); ///////////////////////////////////// INIT of upperBounds
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
					all_distances__[cid].insert(pid, cosinDist(c, ps__->getPoint(pid)));
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
