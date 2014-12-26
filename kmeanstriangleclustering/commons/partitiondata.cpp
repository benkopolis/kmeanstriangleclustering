#include "partitiondata.h"
#include <QFile>

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
    for(QSet<unsigned>& i : clusters)
    {
        i.reserve(points/clusters);
    }
}

void PartitionData::assign(unsigned point, unsigned cluster)
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

void PartitionData::assign_unsafe(unsigned point, unsigned cluster)
{
    this->pointsData.insert(point, cluster);
    while(this->clustersData.size() <= cluster)
        this->clustersData.push_back(QSet<unsigned>);
    this->clustersData[cluster].insert(point);
}

unsigned PartitionData::getCluster(unsigned point) const
{
    return this->pointsData[point];
}

QSet<unsigned> PartitionData::getPoints(unsigned cluster) const
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
        stream << diffs << "/" << from->clustersData.[i].size() << endl;
        total += diffs;
        ++i;
    }
    stream << endl << "Points with various assignment: " << total << endl
           << "Errors %: " << ((float)total / num_points__) *100.0 << endl;
}

void PartitionData::printClusters(QTextStream &stream) const
{
    int i=0;
    for(const QSet<unsigned>& set : this->clustersData)
    {
        stream << i << ':';
        for(const unsigned& point : set)
        {QFile file(fileName);
            if(!file.open(QFile::ReadOnly))
                return false;
            QTextStream in(&file);
            int nClusters=0, nDims = 0;
            in >> nClusters >> nDims;
            int pIndex=0, cIndex=0;
            float coord=0.0;
            char c;
            while(!in.atEnd())
            {
                QString line = in.readLine();
                QTextStream inner(&line);
                while(!inner.atEnd())
                {
                    inner >> pIndex >> c >> coord;
                    points_to_clusters__[pIndex] = cIndex;
                    clusters_to_points__[cIndex]->insert(pIndex);
                }
                ++cIndex;
            }
            compute_centroids();
            file.close();
            return true;
            stream << point << ',';
        }
        stream << endl;
        ++i;
    }
}

void PartitionData::countPreRandIndex()
{
    for(PointId i=0; i < ps__->getNumPoints()-1; ++i)
    {
        int tmp = ps__->getNumPoints()-1;
        if(points_to_clusters__[i] == points_to_clusters__[tmp])
            pre_rand_index__[QPair<PointId, PointId>(i, tmp)] = true;
        for(PointId j= i+1; j < ps__->getNumPoints()-1; ++j)
            if(points_to_clusters__[i] == points_to_clusters__[j])
                pre_rand_index__[QPair<PointId, PointId>(i, j)] = true;
    }
}

bool PartitionData::storePreRandIndex(const QString &fileName) const
{
    logall("KMeans::storePreRandIndex(const QString& fileName) const");
    QFile file(fileName);
    if(pre_rand_index__.size() == 0)
        return false;
    if(!file.open(QFile::WriteOnly))
        return false;
    QTextStream out(&file);
    out << ps__->getNumPoints() << ' ' << num_clusters__ << ' ' << ps__->getNumPoints() << endl;
    QPair<PointId, PointId> p;
    foreach(p, pre_rand_index__.keys())
        out << p.first << ':' << p.second << endl; // write only those pairs that are in the same cluster - rest is in different clusters
    out.flush();
    file.close();
    return true;
}

void PartitionData::printClustersSize(QTextStream &stream) const
{
    for(ClusterId i=0; i < num_clusters__; ++i)
        stream << i << ": " << clusters_to_points__[i]->size() << endl;
}

bool PartitionData::printClusteringResults(const QString &fileName) const
{
    QFile file(fileName);
    if(!file.open(QFile::WriteOnly))
        return false;
    QTextStream stream(&file);
    int i=0;
    stream << num_clusters__ << ' ' << ps__->getNumPoints() << endl; // magic switch ;)
    foreach(const SetPoints* set, clusters_to_points__)
    {
        foreach(const PointId point, *set)
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

bool PartitionData::printCentroids(const QString &fileName) const
{
    QFile file(fileName);
    if(!file.open(QFile::WriteOnly))
        return false;
    QTextStream out(&file);
    foreach(Point p, centroids__)
    {
        foreach(Coord c, p.keys())
            out << c << ':' << p[c] << ' ';
        out << endl;
    }
    out.flush();
    file.close();
    return true;
}


