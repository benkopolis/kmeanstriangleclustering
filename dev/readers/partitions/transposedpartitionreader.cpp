#include "transposedpartitionreader.h"

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

#include <unordered_map>

TransposedPartitionReader::TransposedPartitionReader()
{

}

TransposedPartitionReader::~TransposedPartitionReader()
{

}

PartitionData *TransposedPartitionReader::readFromFile(const char *fileName)
{
    std::ifstream infile(fileName, std::ios::in);
    if (!infile.is_open())
        return nullptr;
    unsigned clusterId, pointId;
    unsigned maxCluster = 0;
    std::unordered_map<unsigned, unsigned> pointToCluster;
    while(!infile.eof())
    {
        infile >> pointId >> clusterId;
        pointToCluster.insert({pointId, clusterId});
        if (clusterId > maxCluster)
            maxCluster = clusterId;
    }

    infile.close();
    PartitionData* data = new PartitionData(maxCluster + 1, unsigned(pointToCluster.size()));
    for(auto pair : pointToCluster)
    {
        data->assign_unsafe(pair.first, pair.second);
    }
    return data;

}

