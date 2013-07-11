#include "kmeanscomparer.h"

KMeansComparer::KMeansComparer(KMeans *first):
    started(false),
    _algorithmsLoop(0),
    _number_of_locks(0)
{
    algorithms.append(first);
}

KMeansComparer::~KMeansComparer()
{
}

void KMeansComparer::runComparsion()
{
    _comparsion = new QSemaphore(algorithms.size());
    foreach(KMeans* alg, algorithms)
        alg->start();
    int running_threads = algorithms.size();
    int tmp_num_of_locks = 0;
    while(running_threads)
    {
        _comparsion->acquire();

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
        running_threads = algorithms.size(); // checking if it should end
        foreach(KMeans* alg, algorithms)
            if(alg->isFinished())
                --running_threads;

    }
}

void KMeansComparer::run()
{
    runComparsion();
}

void KMeansComparer::compare(KMeans* one, KMeans* two)
{

}

void KMeansComparer::waitOnComparer()
{
    _mutex.lock();
    _comparsion->release();
    ++_number_of_locks;
    _mutex.unlock();
    _algorithmsLoop.acquire();
}
