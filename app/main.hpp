#ifndef MAIN_HPP
#define MAIN_HPP

#include "models.hpp"
#include "spaces/pointsspace.h"
#include "spaces/normalizedpointsspace.h"
#include "tfidf/stemmedfileinmemoryparser.h"


Distance dotMatrixes(AbstractPoint const * const a, AbstractPoint const * const b);

Distance cosinDist(const AbstractPoint * const p, const AbstractPoint * const q);

Distance euclideanDist(AbstractPoint const * const p, AbstractPoint const * const q);

void produceClusteringData();

void testClustering();

void testDistances();

void testThreadClustering();

void createTfIdfFile(int argc, char *argv[]);

void performClustering(int argc, char *argv[]);

void comapareDifferentKmeans(int argc, char *argv[]);

void generateResults(int argc, char *argv[]);

void countMeanSquareErrorFromResultFile(int argc, char *argv[]);

void man();

void testArgs();


#endif // MAIN_HPP
