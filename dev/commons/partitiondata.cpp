#include "partitiondata.h"
#include <utility>
#include <fstream>

PartitionData::PartitionData()
{
}

PartitionData::PartitionData(unsigned clusters) :
    clustersData(clusters, std::unordered_set<unsigned>())
{
}

PartitionData::PartitionData(unsigned clusters, unsigned points) :
    clustersData(clusters, std::unordered_set<unsigned>())
{
    this->pointsData.reserve(points);
    for(std::unordered_set<unsigned>& i : this->clustersData)
    {
        i.reserve(points/clusters);
    }
}

void PartitionData::assign(unsigned point, unsigned cluster) throw()
{
    if(this->pointsData.find(point) != this->pointsData.end())
    {
        this->clustersData[this->pointsData[point]].erase(point);
        this->pointsData[point] = cluster;
    }
    else
        this->pointsData.insert(std::make_pair(point, cluster));

    this->clustersData[cluster].insert(point);
}

void PartitionData::assign_unsafe(unsigned point, unsigned cluster) throw()
{
    this->pointsData.insert(std::make_pair(point, cluster));
    while(this->clustersData.size() <= cluster)
        this->clustersData.push_back(std::unordered_set<unsigned>());
    this->clustersData[cluster].insert(point);
}

unsigned PartitionData::getCluster(unsigned point) const throw()
{
    return this->pointsData.at(point);
}

std::unordered_set<unsigned> PartitionData::getPoints(unsigned cluster) const throw()
{
    return this->clustersData[cluster];
}

void PartitionData::printDifferences(const PartitionData *from, std::ostream &stream) const
{
    int i=0, total = 0;
    for(const std::unordered_set<unsigned>& set : this->clustersData)
    {
        stream << i << ": ";
        int diffs = 0;
        for(const unsigned& point: set)
        {
            if(from->clustersData[i].find(point) == from->clustersData[i].end())
                ++diffs;
        }
        stream << diffs << "/" << from->clustersData[i].size() << std::endl;
        total += diffs;
        ++i;
    }
    stream << std::endl << "Points with various assignment: " << total << std::endl
           << "Errors %: " << ((float)total / this->pointsData.size()) *100.0 << std::endl;
}

void PartitionData::printClusters(std::ostream &stream) const
{
    int i=0;
    for(const std::unordered_set<unsigned>& set : this->clustersData)
    {
        stream << i << ':';
        for(const unsigned& point : set)
        {
            stream << point << ',';
        }
        stream << std::endl;
        ++i;
    }
}

void PartitionData::countPreRandIndex()
{
    unsigned numPoints = (unsigned)this->pointsData.size();
    for(unsigned i=0; i < numPoints - 1; ++i)
    {
        int tmp = numPoints - 1;
        if(this->pointsData[i] == this->pointsData[tmp])
            this->pre_rand_index__[std::make_pair(i, tmp)] = true;
        for(unsigned j= i+1; j < numPoints - 1; ++j)
            if(this->pointsData[i] == this->pointsData[j])
                this->pre_rand_index__[std::make_pair(i, j)] = true;
    }
}

bool PartitionData::storePreRandIndex(const std::string &fileName) const
{
    unsigned numPoints = (unsigned)this->pointsData.size();
    std::fstream file(fileName, std::ios_base::out);
    if(this->pre_rand_index__.size() == 0)
        return false;
    if(!file.is_open())
        return false;
    file << numPoints << ' ' << this->clustersData.size() << ' ' << numPoints << std::endl;
    std::unordered_map<std::pair<unsigned, unsigned>, bool>::const_iterator ii = this->pre_rand_index__.begin();
    for(; ii != this->pre_rand_index__.end(); ++ii)
        file << (*ii).first.first << ':' << (*ii).first.second << std::endl; // write only those pairs that are in the same cluster - rest is in different clusters
    file.flush();
    file.close();
    return true;
}

void PartitionData::printClustersSize(std::ostream &stream) const
{
    for(unsigned i=0; i < this->clustersData.size(); ++i)
        stream << i << ": " << this->clustersData[i].size() << std::endl;
}

bool PartitionData::printClusteringResults(const std::string &fileName) const
{
    std::fstream file(fileName, std::ios_base::out);
    if(!file.is_open())
        return false;
    int i=0;
    file << this->clustersData.size() << ' ' << this->pointsData.size() << std::endl; // magic switch ;)
    for(std::vector<std::unordered_set<unsigned> >::const_iterator set = this->clustersData.begin(); set != this->clustersData.end(); ++set)
    {
        for(std::unordered_set<unsigned>::const_iterator point = set->begin() ; point != set->end(); ++point)
        {
            file << (*point) << ':' << "1.0" << ' ';
        }
        file << std::endl;
        ++i;
    }
    file.flush();
    file.close();
    return true;
}

bool PartitionData::printCentroids(const std::string &fileName) const
{
    std::fstream file(fileName, std::ios_base::out);
    if(!file.is_open())
        return false;
    int i = 0;
    for(std::vector<std::unordered_set<unsigned> >::const_iterator set = this->clustersData.begin(); set != this->clustersData.end(); ++set)
    {
        for(std::unordered_set<unsigned>::const_iterator pindex = set->begin() ; pindex != set->end(); ++pindex)
        {
            file << i << ':' << (*pindex) << ' ';
        }
        file << std::endl;
        ++i;
    }
    file.flush();
    file.close();
    return true;
}


