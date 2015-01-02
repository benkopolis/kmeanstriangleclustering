#include "partitiondata.h"
#include <QFile>
#include <QTextStream>
#include <QPair>

PartitionData::PartitionData()
{
}

PartitionData::PartitionData(unsigned clusters) :
    clustersData(clusters, QSet<unsigned>())
{
}

PartitionData::PartitionData(unsigned clusters, unsigned points) :
    clustersData(clusters, QSet<unsigned>())
{
    this->pointsData.reserve(points);
    for(QSet<unsigned>& i : this->clustersData)
    {
        i.reserve(points/clusters);
    }
}

void PartitionData::assign(unsigned point, unsigned cluster) throw()
{
    if(this->pointsData.contains(point))
    {
        this->clustersData[this->pointsData[point]].remove(point);
        this->pointsData[point] = cluster;
    }
    else
        this->pointsData.insert(point, cluster);

    this->clustersData[cluster].insert(point);
}

void PartitionData::assign_unsafe(unsigned point, unsigned cluster) throw()
{
    this->pointsData.insert(point, cluster);
    while(this->clustersData.size() <= cluster)
        this->clustersData.push_back(QSet<unsigned>());
    this->clustersData[cluster].insert(point);
}

unsigned PartitionData::getCluster(unsigned point) const throw()
{
    return this->pointsData[point];
}

QSet<unsigned> PartitionData::getPoints(unsigned cluster) const throw()
{
    return this->clustersData[cluster];
}

void PartitionData::printDifferences(const PartitionData *from, QTextStream &stream) const
{
    int i=0, total = 0;
    for(const QSet<unsigned>& set : this->clustersData)
    {
        stream << i << ": ";
        int diffs = 0;
        for(const unsigned& point: set)
        {
            if(from->clustersData[i].find(point) == from->clustersData[i].end())
                ++diffs;
        }
        stream << diffs << "/" << from->clustersData[i].size() << endl;
        total += diffs;
        ++i;
    }
    stream << endl << "Points with various assignment: " << total << endl
           << "Errors %: " << ((float)total / this->pointsData.size()) *100.0 << endl;
}

bool PartitionData::printClusters(QTextStream &stream) const
{
    int i=0;
    for(const QSet<unsigned>& set : this->clustersData)
    {
        stream << i << ':';
        for(const unsigned& point : set)
        {
            stream << point << ',';
        }
        stream << endl;
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
            pre_rand_index__[QPair<unsigned, unsigned>(i, tmp)] = true;
        for(unsigned j= i+1; j < numPoints - 1; ++j)
            if(this->pointsData[i] == this->pointsData[j])
                pre_rand_index__[QPair<unsigned, unsigned>(i, j)] = true;
    }
}

bool PartitionData::storePreRandIndex(const QString &fileName) const
{
    unsigned numPoints = (unsigned)this->pointsData.size();
    QFile file(fileName);
    if(pre_rand_index__.size() == 0)
        return false;
    if(!file.open(QFile::WriteOnly))
        return false;
    QTextStream out(&file);
    out << numPoints << ' ' << this->clustersData.size() << ' ' << numPoints << endl;
    for(const QPair<unsigned, unsigned>& p : pre_rand_index__.keys())
        out << p.first << ':' << p.second << endl; // write only those pairs that are in the same cluster - rest is in different clusters
    out.flush();
    file.close();
    return true;
}

void PartitionData::printClustersSize(QTextStream &stream) const
{
    for(unsigned i=0; i < this->clustersData.size(); ++i)
        stream << i << ": " << this->clustersData[i]->size() << endl;
}

bool PartitionData::printClusteringResults(const QString &fileName) const
{
    QFile file(fileName);
    if(!file.open(QFile::WriteOnly))
        return false;
    QTextStream stream(&file);
    int i=0;
    stream << num_clusters__ << ' ' << this->pointsData.size() << endl; // magic switch ;)
    for(const QSet<unsigned>& set : this->clustersData)
    {
        for(const unsigned point : set)
        {
            stream << point << ':' << "1.0" << ' ';
        }
        stream << endl;
        ++i;
    }
    stream.flush();
    file.close();
    return true;
}

bool PartitionData::printCentroids(const QString &fileName, AbstractPointsSpace *ps) const
{
    QFile file(fileName);
    if(!file.open(QFile::WriteOnly))
        return false;
    QTextStream out(&file);
    int i = 0;
    for(const QSet<unsigned>& set : this->clustersData)
    {
        for(const unsigned pindex : set)
        {

            foreach(double c, p.keys())
                out << c << ':' << p[c] << ' ';
        }
        out << endl;
    }
    out.flush();
    file.close();
    return true;
}


