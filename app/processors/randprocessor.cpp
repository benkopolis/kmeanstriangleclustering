#include "randprocessor.h"
#include "analysis/randindex.h"

RandProcessor::RandProcessor(int argc, char **argv)
    : AbstractProcessor(argc, argv)
{
    this->_partOne = nullptr;
    this->_partTwo = nullptr;
}

char* RandProcessor::process_internal()
{
    RandIndex ri;
    PartitionData* one = this->_treader.readFromFile(this->_partOne);
    if (one == nullptr)
        one = this->_nreader.readFromFile(this->_partOne);
    PartitionData* two = this->_treader.readFromFile(this->_partTwo);
    if (two == nullptr)
        two = this->_nreader.readFromFile(this->_partTwo);
    double rand = ri.count(one, two);
    char * buffer = new char[100];
    std::snprintf(
                buffer,
                sizeof(buffer),
                "RANDINDEX %.4f\n",
                rand);
    delete one;
    delete two;
    return buffer;
}

void RandProcessor::parse()
{
    if (this->_argc < 6)
        throw "too few args fro rand";
    for(unsigned i = 1; i < this->_argc; i++)
    {
        if (!strcmp(this->_argv[i], "-pone"))
            this->_partOne = this->_argv[i+1];
        else if (!strcmp(this->_argv[i], "-ptwo"))
            this->_partTwo = this->_argv[i+1];
    }
}

