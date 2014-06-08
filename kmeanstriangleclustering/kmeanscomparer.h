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

    void addAlgorithm(KMeans* algorithm);
    inline QString logs() const { return _logs; }

    void runComparsion();
    virtual void compare(KMeans* one, KMeans* two);
    virtual void run();

    void waitOnComparer();

    void notifyAboutThreadEnd();

protected:

    void compareInitialCenters(KMeans* one, KMeans* two);
    void compareCenters(KMeans* one, KMeans* two);
    void universalCentersComparsion(KMeans* one, KMeans* two, QString msg);
    void compareDistances(KMeans* one, KMeans* two);
    void compareEndLoop(KMeans* one, KMeans* two);

    bool shouldThisRun();

    volatile bool started;
    QSemaphore _algorithmsLoop;
    QSemaphore* _comparsion;
    QMutex _mutex;
    QString _logs;

    volatile unsigned int _number_of_locks;
    volatile unsigned int _running_threads;
    QTextStream _log;



    QList<KMeans* > algorithms;

};

#endif // KMEANSCOMPARER_H
