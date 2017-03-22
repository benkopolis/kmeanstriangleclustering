#include "variationofinformationprocessor.h"

#include "analysis/variationofinformationindex.h"

#include <iostream>

VariationOfInformationProcessor::VariationOfInformationProcessor(int argc, char **argv)
    : AbstractProcessor(argc, argv)
{
    this->_partOne = nullptr;
    this->_partTwo = nullptr;
}

char* VariationOfInformationProcessor::process_internal()
{
    VariationOfInformationIndex vi;
    PartitionData* one = this->_treader.readFromFile(this->_partOne);
    if (one == nullptr)
        one = this->_nreader.readFromFile(this->_partOne);
    PartitionData* two = this->_treader.readFromFile(this->_partTwo);
    if (two == nullptr)
        two = this->_nreader.readFromFile(this->_partTwo);
    double vindex = vi.count(one, two);
    char * buffer = new char[100];
    std::snprintf(
                buffer,
                sizeof(buffer),
                "VARIATION_INDEX %.4f\n",
                vindex);
    std::cerr << "VARIATION_INDEX " << vindex << std::endl;
    delete one;
    delete two;
    return buffer;
}

void VariationOfInformationProcessor::parse()
{
    if (this->_argc < 6)
        throw "too few args fro rand";
    for(unsigned i = 1; i < this->_argc; i++)
    {
        std::cerr << this->_argv[i] << std::endl;
        if (!strcmp(this->_argv[i], "-pone"))
            this->_partOne = this->_argv[i+1];
        else if (!strcmp(this->_argv[i], "-ptwo"))
            this->_partTwo = this->_argv[i+1];
    }
}
