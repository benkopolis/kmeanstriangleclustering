#include "abstractdatareader.h"

#ifndef ABSTRACTDATAREADER_CPP
#define ABSTRACTDATAREADER_CPP

#include <string>
#include <iostream>
#include <fstream>

template<typename T>
AbstractDataReader<T>::AbstractDataReader()
{
}

template<typename T>
AbstractPointsSpace<T> *AbstractDataReader<T>::readPointSpaceFromFile(const char* fileName)
{
    std::ifstream *in = new std::ifstream(fileName, std::ios::in);
    if(!in->is_open())
    {
        std::cerr << "Can not open file for reading: " << fileName << std::endl;
        return 0;
    }
    return parseFile(in);
}

#endif //ABSTRACTDATAREADER_CPP
