#ifndef PARTITIONDATA_H
#define PARTITIONDATA_H

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <iostream>
#include <string>
#include "spaces/abstractpointsspace.h"
#include "commons/pair_hash.h"

class PartitionData
{
private:

    PartitionData();
    PartitionData(unsigned clusters);

public:

    PartitionData(unsigned clusters, unsigned points);

    void assign(unsigned point, unsigned cluster) throw();

    void assign_unsafe(unsigned point, unsigned cluster) throw();

    bool is_assigned(unsigned pid) const;

    unsigned getCluster(unsigned point) const throw();

    unsigned assigned_points() const throw();

    const std::unordered_set<unsigned> &getPoints(unsigned cluster) const throw();

    inline unsigned getNumberOfClusters() const throw() { return this->clustersData.size(); }
    inline void setNumberOfClusters(unsigned nclusters) throw() { this->clustersData.resize(nclusters); }

    void printDifferences(const PartitionData* from, std::ostream &stream) const;
    void printClusters(std::ostream& stream) const;
    void countPreRandIndex();
    bool storePreRandIndex(const std::string& fileName) const;
    void printClustersSize(std::ostream& stream) const;
    bool printClusteringResults(const std::string& fileName) const;
    bool printCentroids(const std::string& fileName) const;

private:

    std::unordered_map<unsigned, unsigned> pointsData;
    std::vector<std::unordered_set<unsigned> > clustersData;
    std::unordered_map<std::pair<unsigned, unsigned>, bool> pre_rand_index__;

};

#endif // PARTITIONDATA_H
