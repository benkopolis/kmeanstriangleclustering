#include "kmeanstriangle.hpp"
#include "models.hpp"
#include <limits>
#include <QtConcurrentMap>

KMeansTriangle::KMeansTriangle(ClusterId nclusters, unsigned int numIters, AbstractPointsSpace* ps, bool store) :
	KMeans(nclusters, numIters, ps, store),
	conditions_use_counter__(0),
	sVector__(nclusters, std::numeric_limits<Distance>::max()),
	centersToCenters__(nclusters, QVector<Distance>(nclusters, 0.0)),
	lowerBounds__(nclusters, QVector<Distance>(ps->getNumPoints(), 0.0)),
    upperBounds__(ps->getNumPoints(), std::numeric_limits<Distance>::max()),
	new_centroids__(nclusters, Point()),
    rVector__(ps->getNumPoints())
{
    logall("KMeansTriangle::KMeansTriangle");
}


void KMeansTriangle::compute_centroids()
{
    logall("KMeansTriangle::compute_centroids()");
	Dimensions i;
	PointId num_points_in_cluster;
    // for each centroid
    for(int cid = 0, clusters = centroids__.size(); clusters < cid; ++cid)
	{
        logall(QString("Center %1 has points: ").arg(QString::number(cid)));
		num_points_in_cluster = 0;
		for(unsigned int crd = 0; crd < num_dimensions__; ++crd)
			new_centroids__[cid][crd] = 0;
        // for earch PointId in this set
        foreach(PointId pid, *clusters_to_points__[cid])
        {
            logoneline(QString("%1, ").arg(QString::number(pid)));
			Point p = ps__->getPoint(pid);
			for (i=0; i<num_dimensions__; i++)
				new_centroids__[cid][i] += p[i];
			num_points_in_cluster++;
		}
		// if no point in the clusters, this goes to inf (correct!)
        logall(QString("Center %1 has coords: ").arg(QString::number(cid)));
        for (i=0; i<num_dimensions__; i++)
        {
			new_centroids__[cid][i] /= num_points_in_cluster;
            logoneline(QString("%1:%2, ").arg(QString::number(i), QString::number(new_centroids__[cid][i])));
        }
	}
}

void KMeansTriangle::count_centers_distances(const Centroids& centroids)
{
    logall("KMeansTriangle::count_centers_distances()");
    for (unsigned int a = 0, total_minus_one = (unsigned)centroids.size() - 1; a < total_minus_one; ++a)
    {
        centersToCenters__[a][a] = 0;
        for (unsigned int b = a + 1, total = total_minus_one + 1; b < total; ++b)
        {
            centersToCenters__[a][b] = centersToCenters__[b][a] =
                    countDistance(centroids[a], centroids[b]);
            logall(QString("Distance between center %1 and %2 is %3").arg(
                       QString::number(a), QString::number(b),
                       QString::number(centersToCenters__[a][b])));
        }
    }
}

void KMeansTriangle::assignDSVectors()
{
    logall("KMeansTriangle::assignDSVectors()");
    count_centers_distances(new_centroids__);
    logall("SVector values for centers: ");
    for (unsigned int a = 0; a < num_clusters__; ++a)
	{
        for (unsigned int b = 0; b < num_clusters__; ++b)
        {
            if(a == b)
                continue;
            if (sVector__[a] > centersToCenters__[a][b]/2.0)
                sVector__[a] = centersToCenters__[a][b]/2.0;
        }
        logoneline(QString("%1:%2, ").arg(QString::number(a), QString::number(sVector__[a])));
	}
}


void KMeansTriangle::initial_partition_points()
{
    logall("KMeansTriangle::initial_partition_points()");
    ClusterId cid;
    QHash<ClusterId, unsigned int> numOfPointsInCLusters;
    for(unsigned int total = (unsigned int)centroids__.size(), i =0; i < total; ++i)
        numOfPointsInCLusters.insert(i, 0);
    for (PointId pid = 0; pid < ps__->getNumPoints(); pid++)
    {
        Point p = ps__->getPoint(pid);
        cid = pid % num_clusters__;
        foreach (unsigned int index, p.keys()) {
            centroids__[cid][index] += p[index];
        }
        numOfPointsInCLusters[cid] += 1;
    }

    for(unsigned int total = (unsigned int)centroids__.size(), i =0; i < total; ++i) {

        foreach (unsigned int index, centroids__[i].keys()) {
            centroids__[i][index] /= numOfPointsInCLusters[i];
        }

    }
}

void KMeansTriangle::move_point_initial(unsigned int pid, Distance d, unsigned int cid)
{
    upperBounds__[pid] = d;
    if(points_to_clusters__.contains(pid))
        clusters_to_points__[points_to_clusters__[pid]]->remove(pid);

    clusters_to_points__[cid]->insert(pid);
    if(!points_to_clusters__.contains(pid))
        points_to_clusters__.insert(pid, cid);
    else
        points_to_clusters__[pid] = cid;
}

void KMeansTriangle::init_bounds()
{
    logall("KMeansTriangle::init_bounds()");
    count_centers_distances(centroids__);
    QTextStream out(stdout);
    for (unsigned int pid = 0, upperSize = (unsigned)upperBounds__.size(); pid < upperSize; ++pid)
    {
        //this->printClustersSize(out << "------------ SIZE --------------- " << endl);
        for(unsigned int cid = 0, clusters = (unsigned)centroids__.size(); cid < clusters; ++cid)
        {
            if(!points_to_clusters__.contains(pid) ||
                    centersToCenters__[points_to_clusters__[pid]][cid] < upperBounds__[pid] ||
                    centersToCenters__[points_to_clusters__[pid]][cid] < 2*upperBounds__[pid])
            {
                Distance d = countDistance(ps__->getPoint(pid),
                                           centroids__[cid]);
                lowerBounds__[cid][pid] = d;
                if(upperBounds__[pid] > d)
                {
                    move_point_initial(pid, d, cid);
                }
            }
            else
                lowerBounds__[cid][pid] = lowerBounds__[points_to_clusters__[pid]][pid];

            {
            logall(QString("Lower bound of point %1 with center %2 is %3").arg(
                       QString::number(pid),
                       QString::number(cid),
                       QString::number(lowerBounds__[cid][pid])));
            }
        }
        logall(QString("Upper bound of point %1 is %2").arg(QString::number(pid), QString::number(upperBounds__[pid])));
    }
}

void KMeansTriangle::computeLowerAndUpperBounds()
{
    logall("KMeansTriangle::computeLowerAndUpperBounds()");
	QVector<Distance> delta(this->num_clusters__);
    logall("Delta values for ever center: ");

    for (unsigned int cid = 0; cid < (unsigned)centroids__.size(); ++cid)
    {
        delta[cid] = countDistance(centroids__[cid], new_centroids__[cid]);
        logoneline(QString("%1:%2, ").arg(QString::number(cid), QString::number(delta[cid])));
    }

    logall("Lower and upper bouds!");

    for (unsigned int pid = 0; pid < (unsigned)upperBounds__.size(); ++pid)
	{
        logall(QString("Lower bounds of point %1 per each center").arg(QString::number(pid)));
        for (unsigned int cid = 0; cid < (unsigned)centroids__.size(); ++cid)
		{
            lowerBounds__[cid][pid] = lowerBounds__[cid][pid] - delta[cid];
//                    fabs(lowerBounds__[pid][cid] - delta[cid]);
            if (lowerBounds__[cid][pid] < 0)
                lowerBounds__[cid][pid] = 0;

            logoneline(QString("%1:%2, ").arg(QString::number(cid), QString::number(lowerBounds__[cid][pid])));
		}

        upperBounds__[pid] += delta[points_to_clusters__[pid]];
        logall(QString("Upper bound of point %1 is %2").arg(QString::number(pid), QString::number(upperBounds__[pid])));
	}
}

void KMeansTriangle::move_point(unsigned int pid, ClusterId to_cluster)
{
    logall("KMeansTriangle::move_point(unsigned int pid, ClusterId to_cluster, bool* move)");
    clusters_to_points__[to_cluster]->insert(pid);
    clusters_to_points__[points_to_clusters__[pid]]->remove(pid);
    points_to_clusters__[pid] = to_cluster;
    upperBounds__[pid] = lowerBounds__[to_cluster][pid];
    rVector__[pid].notCounted = false;
    ++num_moved__;
    logall(QString("Moving point %1 to center %2").arg(
               QString::number(pid),
               QString::number(to_cluster)));
}

bool KMeansTriangle::computePointsAssignements(QTextStream& log)
{
    logall("KMeansTriangle::computePointsAssignements(QTextStream& log)");
	bool change = false;
	bool move = false;
	ClusterId to_cluster = 0;
    Distance d;
    for (unsigned int pid = 0; pid < (unsigned)upperBounds__.size(); ++pid)
	{
        {
        logall(QString("upperBounds[%1](%2) > sVector[%3](%4) ---- condition is %5").arg(
                   QString::number(pid),
                   QString::number(upperBounds__[pid]),
                   QString::number(points_to_clusters__[pid]),
                   QString::number(sVector__[points_to_clusters__[pid]]),
                   QString::number(upperBounds__[pid] > sVector__[points_to_clusters__[pid]])));
        }

        // 1. identify all points that are u(x) =< s(c(x)), and skip them
		if (upperBounds__[pid] > sVector__[points_to_clusters__[pid]])
        {
            for (unsigned int a = 0, clusters = (unsigned)centroids__.size(); a < clusters; ++a)
            { // 2. for all remaining points
                {
                logall(QString("upperBounds[%1](%2) < sVector[%3](%4) ---- condition is %5").arg(
                           QString::number(pid),
                           QString::number(upperBounds__[pid]),
                           QString::number(a),
                           QString::number(sVector__[a]),
                           QString::number(upperBounds__[pid] < sVector__[a])));
                }

                if(a == points_to_clusters__[pid])
                    continue;

                //if(upperBounds__[pid] < sVector__[a])
                //	continue;
                {
                logall(QString("%1 != %2 &&\n upperBounds(%3) > lowerBounds(%4) &&\n upperBounds(%5) > centersToCenters__(%6)/2.0 ---- condition is %7").arg(
                           QString::number(a),
                           QString::number(points_to_clusters__[pid]),
                           QString::number(upperBounds__[pid]),
                           QString::number(lowerBounds__[a][pid]),
                           QString::number(upperBounds__[pid]),
                           QString::number(centersToCenters__[points_to_clusters__[pid]][a]),
                           QString::number(a != points_to_clusters__[pid] &&
                                upperBounds__[pid] > lowerBounds__[a][pid] &&
                                upperBounds__[pid] > centersToCenters__[points_to_clusters__[pid]][a]/2.0)));
                }

                // for points that are: u(x) > l(x,c) and u(x) > 1/2*d(c,c(x))
                if (upperBounds__[pid] > lowerBounds__[a][pid] &&
                        upperBounds__[pid] > centersToCenters__[points_to_clusters__[pid]][a]/2.0)
				{
                    // if r(x) is true count d = d(c(x), x)
                    if (rVector__[pid].notCounted)
					{
                        rVector__[pid].distance =
                                countDistance(ps__->getPoint(pid),
                                              centroids__[points_to_clusters__[pid]]);
                        rVector__[pid].notCounted = false;
                        modifiedR.push(pid);
					}
                    else // d = u(x)
                        rVector__[pid].distance = upperBounds__[pid];
                    {
                    logall(QString("rVector for point %1 is %2 and distance is %3").arg(
                               QString::number(pid),
                               QString::number(rVector__[pid].notCounted)));
                    }

                    // if d > l(x, c) or d > 1/2*d(c,c(x)) then compute d(c,x)
                    if(rVector__[pid].distance > lowerBounds__[a][pid]
                            || rVector__[pid].distance > centersToCenters__[points_to_clusters__[pid]][a]/2.0)
                    {
                        d = countDistance(ps__->getPoint(pid), centroids__[a]);
                     {
                        logall(QString("Distance from point %1 to center %2 is %3").arg(
                                   QString::number(pid),
                                   QString::number(a),
                                   QString::number(d)));
                    }

                        if(d < rVector__[pid].distance) // move
						{
                            rVector__[pid].distance = d;
                            clusters_to_points__[points_to_clusters__[pid]]->remove(pid);
							move = true;
							change = true;
							to_cluster = a;
						}
					}
				}
			} // all centers checked
			if(move)
                move_point(pid, to_cluster);
            move = false;
		}
	}
	return change;
}

/***
  * Method for executing k-means clustering algorithm with traingle inequality
  */
void KMeansTriangle::executeAlgorithm()
{
    logall("KMeansTriangle::executeAlgorithm()");
	QTextStream out(stdout);
	QFile log_file__("log_algh.txt");
	QTextStream* log_stream__;
	if(log_file__.open(QFile::WriteOnly))// | QFile::Append))
		log_stream__ = new QTextStream(&log_file__);
	else
		log_stream__ = new QTextStream(stdout);
	bool some_point_is_moving = true;
	unsigned int num_iterations = 0;

	// Initial partition of points
	initial_partition_points();
    init_bounds();
//    compute_centroids();
//    this->computeLowerAndUpperBounds();
    num_iterations = 0;
    do
	{
        logall(QString("Iteration %1").arg(QString::number(num_iterations)));
		some_point_is_moving = false;
        for(int i=0; i<sVector__.size(); ++i)
            sVector__[i] = std::numeric_limits<Distance>::max();
        compute_centroids();
        this->computeLowerAndUpperBounds();

        ++num_iterations;
        this->assignDSVectors();
        some_point_is_moving = this->computePointsAssignements(*log_stream__);

        while(!modifiedR.isEmpty())
            rVector__[modifiedR.pop()].reset();
        centroids__ = new_centroids__;

        logall(QString("Iteration %1, points moving: %2").arg(
                   QString::number(num_iterations),
                   QString::number(some_point_is_moving)));
    } while (some_point_is_moving && num_iterations <= iterationsCount__);

	used_iterations__ = num_iterations;
	(*log_stream__).flush();
	log_file__.close();
	delete log_stream__;
}

void KMeansTriangle::storeCurrentIterationState()
{
    logall("KMeansTriangle::storeCurrentIterationState()");
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
    stream.flush();
    iterations_states__.push_back(status);
}









