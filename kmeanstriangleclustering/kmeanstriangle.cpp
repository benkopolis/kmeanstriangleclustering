#include "kmeanstriangle.hpp"
#include "kmeanscomparer.h"
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
	for(int cid = 0; cid < centroids__.size(); ++cid)
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

void KMeansTriangle::assignDSVectors()
{
    logall("KMeansTriangle::assignDSVectors()");
    for (unsigned int a = 0; a < (unsigned)centroids__.size() - 1; ++a)
	{
		centersToCenters__[a][a] = 0;
        for (unsigned int b = a + 1; b < (unsigned)centroids__.size(); ++b)
        {
            centersToCenters__[a][b] = centersToCenters__[b][a] =
                    countDistance(centroids__[a], centroids__[b]);
            logall(QString("Distance between center %1 and %2 is %3").arg(
                       QString::number(a), QString::number(b),
                       QString::number(centersToCenters__[a][b])));
        }
	}
    logall("SVector values for centers: ");
    for (unsigned int a = 0; a < (unsigned)centroids__.size(); ++a)
	{
        for (unsigned int b = 0; b < (unsigned)centroids__.size(); ++b)
        {
            if(a == b)
                continue;
            if (sVector__[a] > centersToCenters__[a][b]/2.0)
                sVector__[a] = centersToCenters__[a][b]/2.0;
            logoneline(QString("%1:%2, ").arg(QString::number(a), QString::number(sVector__[a])));
        }
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
    for (unsigned int pid = 0; pid < (unsigned)lowerBounds__.size(); ++pid)
	{
        logall(QString("Lower bounds of point %1 per each center").arg(QString::number(pid)));
        for (unsigned int cid = 0; cid < (unsigned)centroids__.size(); ++cid)
		{
            lowerBounds__[pid][cid] = lowerBounds__[pid][cid] - delta[cid];
//                    fabs(lowerBounds__[pid][cid] - delta[cid]);
            if (lowerBounds__[pid][cid] < 0)
                lowerBounds__[pid][cid] = 0;
            logoneline(QString("%1:%2, ").arg(QString::number(cid), QString::number(lowerBounds__[pid][cid])));
		}
		upperBounds__[pid] += delta[points_to_clusters__[pid]];
        logall(QString("Upper bound of point %1 is %2").arg(QString::number(pid), QString::number(upperBounds__[pid])));
	}
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
        logall(QString("upperBounds[%1](%2) > sVector[%3](%4) ---- condition is %5").arg(
                   QString::number(pid),
                   QString::number(upperBounds__[pid]),
                   QString::number(points_to_clusters__[pid]),
                   QString::number(sVector__[points_to_clusters__[pid]]),
                   QString::number(upperBounds__[pid] > sVector__[points_to_clusters__[pid]])));
		if (upperBounds__[pid] > sVector__[points_to_clusters__[pid]])
		{
            for (unsigned int a = 0; a < (unsigned)centroids__.size(); ++a)
			{
                logall(QString("upperBounds[%1](%2) < sVector[%3](%4) ---- condition is %5").arg(
                           QString::number(pid),
                           QString::number(upperBounds__[pid]),
                           QString::number(a),
                           QString::number(sVector__[a]),
                           QString::number(upperBounds__[pid] < sVector__[a])));
                if(upperBounds__[pid] < sVector__[a])
					continue;
                logall(QString("%1 != %2 &&\n upperBounds(%3) > lowerBounds(%4) &&\n upperBounds(%5) > centersToCenters__(%6)/2.0 ---- condition is %7").arg(
                           QString::number(a),
                           QString::number(points_to_clusters__[pid]),
                           QString::number(upperBounds__[pid]),
                           QString::number(lowerBounds__[pid][a]),
                           QString::number(upperBounds__[pid]),
                           QString::number(centersToCenters__[points_to_clusters__[pid]][a]),
                           QString::number(a != points_to_clusters__[pid] &&
                                upperBounds__[pid] > lowerBounds__[pid][a] &&
                                upperBounds__[pid] > centersToCenters__[points_to_clusters__[pid]][a]/2.0)));
				if (a != points_to_clusters__[pid] &&
                        upperBounds__[pid] > lowerBounds__[pid][a] &&
                        upperBounds__[pid] > centersToCenters__[points_to_clusters__[pid]][a]/2.0)
				{
                    if (rVector__[pid].notCounted)
					{
                        rVector__[pid].distance =
                                countDistance(ps__->getPoint(pid),
                                              centroids__[points_to_clusters__[pid]]);
                        rVector__[pid].notCounted = false;
                        modifiedR.push(pid);
					}
					else
                        rVector__[pid].distance = upperBounds__[pid];
                    logall(QString("rVector for point %1 is %2 and distance is %3").arg(
                               QString::number(pid),
                               QString::number(rVector__[pid].notCounted)));
                    if(rVector__[pid].distance > lowerBounds__[pid][a]
                            || rVector__[pid].distance > sVector__[a])
                    {
                        d = countDistance(ps__->getPoint(pid), centroids__[a]);
                        logall(QString("Distance from point %1 to center %2 is %3").arg(
                                   QString::number(pid),
                                   QString::number(a),
                                   QString::number(d)));
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
			{
				log << pid << ':' << points_to_clusters__[pid] << '>' << to_cluster << endl;
                clusters_to_points__[to_cluster]->insert(pid);
				points_to_clusters__[pid] = to_cluster;
                upperBounds__[pid] = lowerBounds__[pid][to_cluster];
                rVector__[pid].notCounted = false;
				move = false;
				++num_moved__;
                logall(QString("Moving point %1 to center %2").arg(
                           QString::number(pid),
                           QString::number(to_cluster)));
			}
		}
	}
	return change;
}

void KMeansTriangle::initial_partition_points()
{
    logall("KMeansTriangle::initial_partition_points()");
	ClusterId cid;
	for (PointId pid = 0; pid < ps__->getNumPoints(); pid++)
	{
		cid = pid % num_clusters__;
		points_to_clusters__.push_back(cid);
        clusters_to_points__[cid]->insert(pid);
	}
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
    compute_centroids();
//    assignDSVectors();
//	firstLoop(*log_stream__);
//    compute_centroids();
//	this->computeLowerAndUpperBounds();
    num_iterations = 0;
    do
	{
        logall(QString("Itaration %1").arg(QString::number(num_iterations)));
		some_point_is_moving = false;
        for(int i=0; i<sVector__.size(); ++i)
            sVector__[i] = std::numeric_limits<Distance>::max();
		++num_iterations;
		this->assignDSVectors();
		some_point_is_moving = this->computePointsAssignements(*log_stream__);
        compute_centroids();
		this->computeLowerAndUpperBounds();
        while(!modifiedR.isEmpty())
            rVector__[modifiedR.pop()].reset();
        centroids__ = new_centroids__;
    } while (some_point_is_moving && num_iterations <= iterationsCount__);

	used_iterations__ = num_iterations;
	(*log_stream__).flush();
	log_file__.close();
	delete log_stream__;
}

void KMeansTriangle::firstLoop(QTextStream& log)
{\
    logall("KMeansTriangle::firstLoop(QTextStream& log)");
	ClusterId to_cluster;
	Distance d, min;
	bool move = false;
	for(PointId pid = 0; pid < ps__->getNumPoints(); ++pid)
	{
        min = countDistance(centroids__[points_to_clusters__[pid]],
			ps__->getPoint(pid));
        lowerBounds__[pid][points_to_clusters__[pid]] = min;
		upperBounds__[pid] = min;
		for(ClusterId cid =0; cid < num_clusters__; ++cid)
		{
			if(cid != points_to_clusters__[pid])
			{
                d = countDistance(centroids__[cid], ps__->getPoint(pid));
                lowerBounds__[pid][cid] = d;
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
            clusters_to_points__[points_to_clusters__[pid]]->remove(pid);
			points_to_clusters__[pid] = to_cluster;
            clusters_to_points__[to_cluster]->insert(pid);
			++num_moved__;
		}
	}
    if(store_states__)
        this->storeCurrentIterationState();
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









