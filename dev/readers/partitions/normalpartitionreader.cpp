#include "normalpartitionreader.h"

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

#include <unordered_map>

NormalPartitionReader::NormalPartitionReader()
{

}

NormalPartitionReader::~NormalPartitionReader()
{

}

PartitionData *NormalPartitionReader::readFromFile(const char *fileName)
{
    std::ifstream infile(fileName, std::ios::in);
    if (!infile.is_open())
        return nullptr;
    unsigned clusterId, clusterNum = 0;
    std::unordered_map<unsigned, unsigned> pointToCluster;
    while(!infile.eof())
    {
        std::string line;
        std::getline(infile, line);
        if(line.empty())
            continue;
        std::stringstream line_in(std::ios::in);
        line_in.str(line);
        line_in.seekg(0, std::ios_base::beg);
        unsigned pointId;
        char c;
        line_in >> clusterId >> c;
        while(!line_in.eof())
        {
            line_in >> pointId;
            pointToCluster.insert({pointId, clusterId});
        }
        ++clusterNum;
    }

    infile.close();
    PartitionData* data = new PartitionData(clusterNum, unsigned(pointToCluster.size()));
    for(auto pair : pointToCluster)
    {
        data->assign_unsafe(pair.first, pair.second);
    }
    return data;
}

