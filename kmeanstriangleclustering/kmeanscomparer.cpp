#include "kmeanscomparer.h"

KMeansComparer::KMeansComparer():
    started(false),
    _algorithmsLoop(0),
    _number_of_locks(0),
    _running_threads(0),
    _log(&_logs)
{
}

KMeansComparer::~KMeansComparer()
{
    algorithms.clear();
}

void KMeansComparer::addAlgorithm(KMeans* algorithm)
{
    algorithms << algorithm;
    algorithm->setMonitor(this);
}

void KMeansComparer::runComparsion()
{
    _comparsion = new QSemaphore(algorithms.size());
    foreach(KMeans* alg, algorithms)
        alg->start();
    _running_threads = algorithms.size();
    int tmp_num_of_locks = 0;
    do {
        if(!this->shouldThisRun())
            break;
        if(_running_threads > 1)
            _comparsion->acquire(_running_threads);
        else
            break;
        foreach(KMeans* one, algorithms)
            foreach(KMeans* two, algorithms)
                if(one != two)
                    this->compare(one, two);

        _mutex.lock(); // releasing locks on algorithms
        tmp_num_of_locks = _number_of_locks;
        _number_of_locks = 0;
        _mutex.unlock();
        _algorithmsLoop.release(tmp_num_of_locks);
        tmp_num_of_locks = 0;
        if(!this->shouldThisRun())
            break;
    } while(this->shouldThisRun());
}

void KMeansComparer::run()
{
    runComparsion();
}

void KMeansComparer::compare(KMeans* one, KMeans* two)
{
    if(one->getAlgorithmPosition() != two->getAlgorithmPosition())
        return;
    KMeans::AlgorithmPosition position = one->getAlgorithmPosition();
    switch(position)
    {
        case KMeans::InitialClusters:
            this->compareInitialCenters(one, two);
            break;
        case KMeans::CentersComputed:
            this->compareCenters(one, two);
            break;
        case KMeans::DistancesCounted:
            this->compareDistances(one, two);
            break;
        case KMeans::EndLoop:
            this->compareEndLoop(one, two);
            break;
        default:
            break;
    }
}

void KMeansComparer::compareInitialCenters(KMeans* one, KMeans* two)
{
    this->universalCentersComparsion(one, two, "INITIAL CENTERS");
}

void KMeansComparer::compareCenters(KMeans* one, KMeans* two)
{
    this->universalCentersComparsion(one, two, "CENTERS");
}

void KMeansComparer::universalCentersComparsion(KMeans* one,
                                                KMeans* two, QString msg)
{
    _log << msg << " comparsion BEGIN" << endl;
    bool found = false;
    foreach(Point p, one->centroids__)
    {
        foreach(Point q, two->centroids__)
        {
            if(p == q)
            {
                found = true;
                break;
            }
        }
        if(!found)
            _log << "No match for centroid at "
                 << one->centroids__.indexOf(p) << " index in ONE"
                 << endl;
        else
            found = false;
    }

    _log << msg << " comparsion END" << endl;
}

void KMeansComparer::compareDistances(KMeans* one, KMeans* two)
{
    Distances fromOne = one->all_distances__,
              fromTwo = two->all_distances__;
    _log << "DISTANCES comparsion BEGIN" << endl;
    for(unsigned int i=0; i<one->num_points__; ++i)
    {
        for(unsigned int j=i+1; j<one->num_points__; ++j)
        {
            if(!fromOne.contains(i))
            {
                if(!fromTwo.contains(i))
                    continue;
                else if(fromTwo[i].contains(j))
                {
                    _log << "p[" << i << "][" << j << "]=NULL "
                         << "q[" << i << "][" << j << "]="
                         << fromTwo[i][j] << endl;
                }
            }
            else if(fromOne[i].contains(j))
            {
                if(!fromTwo.contains(i) || !fromTwo[i].contains(j))
                    _log << "p[" << i << "][" << j << "]= "
                         << fromOne[i][j] << "q[" << i << "]["
                         << j << "]=NULL" << endl;
                else if(fromTwo.contains(i) && fromTwo[i].contains(j)
                        && fromOne[i][j] != fromTwo[i][j])
                    _log << "p[" << i << "][" << j << "]= "
                         << fromOne[i][j] << "q[" << i << "]["
                         << j << "]=" << fromTwo[i][j] << endl;
            }
        }
    }
    _log << "DISTANCES comparsion END" << endl;
}

void KMeansComparer::compareEndLoop(KMeans* one, KMeans* two)
{
    int *tmpTab = new int [one->num_clusters__];
    for(unsigned int i=0; i<one->num_clusters__; ++i)
        tmpTab = 0;
    _log << "CLUSTERS comparsion BEGIN" << endl;
    for(ClusterId cid =0; cid < one->num_clusters__; ++cid)
    {
        foreach(PointId pid, *(one->clusters_to_points__[cid]))
        {
            ++tmpTab[two->points_to_clusters__[pid]];
        }
        _log << "for ONE cluster " << cid << "("
             << one->clusters_to_points__[cid]->size() << "):" << endl;
        _log << "from above in TWO clusters: " << endl;
        for(unsigned int i=0; i<one->num_clusters__; ++i)
        {
            _log << "cid: " << i << " size: " << tmpTab[i];
            tmpTab[i] = 0;
        }
    }
    delete [] tmpTab;
    tmpTab = 0;
    _log << "CLUSTERS comparsion END" << endl;
}

bool KMeansComparer::shouldThisRun()
{
    _mutex.lock();
    bool b = _running_threads > 0;
    _mutex.unlock();
    return b;
}

void KMeansComparer::notifyAboutThreadEnd()
{
    _mutex.lock();
    --_running_threads;
    if((unsigned)_comparsion->available() > _running_threads)
        _comparsion->release(_comparsion->available() - _running_threads);
    _mutex.unlock();
}

void KMeansComparer::waitOnComparer()
{
    _mutex.lock();
    _comparsion->release();
    ++_number_of_locks;
    _mutex.unlock();
    if(_running_threads < 2)
        return;
    _algorithmsLoop.acquire();
}
