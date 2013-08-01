#ifndef KMEANSCOMPARER_H
#define KMEANSCOMPARER_H

#include <QList>
#include <QSemaphore>

#include "KMeans.hpp"
#include <QTextStream>


class KMeansComparer : public QThread
{
public:
    KMeansComparer();

    virtual ~KMeansComparer();

    inline void addAlgorithm(KMeans* algorithm) { algorithms.append(algorithm); }
    inline QString logs() const { return _logs; }

    void runComparsion();
    virtual void compare(KMeans* one, KMeans* two);
    virtual void run();

    void waitOnComparer();

protected:

    void compareInitialCenters(KMeans* one, KMeans* two);
    void compareCenters(KMeans* one, KMeans* two);
    void universalCentersComparsion(KMeans* one, KMeans* two, QString msg);
    void compareDistances(KMeans* one, KMeans* two);
    void compareEndLoop(KMeans* one, KMeans* two);

    QSemaphore _algorithmsLoop;
    QSemaphore* _comparsion;
    QMutex _mutex;
    QString _logs;
    QTextStream _log;

    unsigned int _number_of_locks;
    QList<KMeans* > algorithms;
    bool started;
};

#endif // KMEANSCOMPARER_H
