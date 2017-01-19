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

bool PartitionData::is_assigned(unsigned pid) const
{
    return this->pointsData.count(pid) > 0;
}

unsigned PartitionData::getCluster(unsigned point) const throw()
{
    return this->pointsData.at(point);
}

unsigned PartitionData::assigned_points() const throw()
{
    return this->pointsData.size();
}

const std::unordered_set<unsigned>& PartitionData::getPoints(unsigned cluster) const throw()
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

void PartitionData::printClusters(const char *fileName) const
{
    std::ofstream file;
    file.open(fileName, std::ofstream::out);
    this->printClusters(file);
    file.close();
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

void PartitionData::printClustersTransposed(const char *fileName) const
{
    std::ofstream file;
    file.open(fileName, std::ofstream::out);
    this->printClustersTransposed(file);
    file.close();
}

void PartitionData::printClustersTransposed(std::ostream &stream) const
{
    for(auto pidToCid : this->pointsData)
    {
        stream << pidToCid.first << " " << pidToCid.second << std::endl;
    }
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


