#ifndef MAIN_HPP
#define MAIN_HPP

#include <QtCore/QCoreApplication>
#include "models.hpp"
#include "KMeans.hpp"
#include "kmeanstriangle.hpp"
#include "spaces/pointsspace.h"
#include "spaces/normalizedpointsspace.h"
#include "tfidf/stemmedfileinmemoryparser.h"


Distance dotMatrixes(AbstractPoint *a, AbstractPoint *b);

Distance cosinDist(AbstractPoint *p, AbstractPoint *q);

Distance euclideanDist(AbstractPoint *p, AbstractPoint *q);

void produceClusteringData();

void executeAndPrintClusteringResults(QTextStream* stream, QTextStream& out, KMeans* clusters, QString message);

void executeAndPrintClusteringResults(QTextStream* stream, QTextStream& out, KMeans &clusters, QString message);

void testClustering();

void testDistances();

void testThreadClustering();

void createTfIdfFile(int argc, char *argv[]);

QString getOutputFileName(QString input, QString fileType,
                          int num_clusters, int num_iters);

QString getPreRandFileName(QString input, int num_clusters,
                           int num_iters);

QString getResultsFileName(QString input, int num_clusters,
                           int num_iters);

QString getCentroidsFileName(QString input, int num_clusters,
                             int num_iters);

void printManForComparsion(QTextStream& out);

AbstractPointsSpace* generateProperPointSpace(char *argv[], QTextStream& out);

void comapareDifferentKmeans(int argc, char *argv[]);

void generateResults(int argc, char *argv[]);

void countMeanSquareErrorFromResultFile(int argc, char *argv[]);

void man();

void testArgs();


#endif // MAIN_HPP
