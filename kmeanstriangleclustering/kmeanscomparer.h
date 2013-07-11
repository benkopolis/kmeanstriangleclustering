#ifndef KMEANSCOMPARER_H
#define KMEANSCOMPARER_H

#include <QList>
#include <QSemaphore>
#include "KMeans.hpp"

class KMeansComparer : public QThread
{
public:
    KMeansComparer(KMeans* first);

    virtual ~KMeansComparer();

    inline void addAlgorithm(KMeans* algorithm) { algorithms.append(algorithm); }

    void runComparsion();
    virtual void compare(KMeans* one, KMeans* two);
    virtual void run();

    void waitOnComparer();

protected:

    QSemaphore _algorithmsLoop;
    QSemaphore* _comparsion;
    QMutex _mutex;

    unsigned int _number_of_locks;
    QList<KMeans* > algorithms;
    bool started;
};

#endif // KMEANSCOMPARER_H
