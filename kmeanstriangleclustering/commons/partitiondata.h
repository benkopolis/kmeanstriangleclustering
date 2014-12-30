#ifndef PARTITIONDATA_H
#define PARTITIONDATA_H

#include <vector>
#include <QHash>
#include <QSet>
#include <QTextStream>
#include "spaces/abstractpointsspace.h"

class PartitionData
{
public:
    PartitionData();
    PartitionData(unsigned clusters);
    PartitionData(unsigned clusters, unsigned points);

    void assign(unsigned point, unsigned cluster) throw();

    void assign_unsafe(unsigned point, unsigned cluster) throw();

    unsigned getCluster(unsigned point) const throw();

    QSet<unsigned> getPoints(unsigned cluster) const throw();

    inline unsigned getNumberOfClusters() const throw() { return this->clustersData.size(); }
    inline void setNumberOfClusters(unsigned nclusters) throw() { this->clustersData.resize(nclusters); }

    void printDifferences(const PartitionData* from, QTextStream& stream) const;
    bool printClusters(QTextStream& stream) const;
    void countPreRandIndex();
    bool storePreRandIndex(const QString& fileName) const;
    void printClustersSize(QTextStream& stream) const;
    bool printClusteringResults(const QString& fileName) const;
    bool printCentroids(const QString& fileName, AbstractPointSpace *ps) const;

private:

    QHash<unsigned, unsigned> pointsData;
    std::vector<QSet<unsigned> > clustersData;
    QHash<QPair<unsigned, unsigned>, bool> pre_rand_index__;
};

#endif // PARTITIONDATA_H
