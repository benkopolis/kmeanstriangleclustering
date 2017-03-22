#include "silhouetteprocessor.h"

#include "analysis/silhouetteindex.h"
#include "distances/cosinedistance.h"
#include "distances/euclideandistance.h"
#include "distances/hamiltondistance.h"
#include "distances/manhattandistance.h"
#include "spaces/abstractpointsspace.h"

#include <iostream>

SilhouetteProcessor::SilhouetteProcessor(int argc, char **argv)
    : AbstractProcessor(argc, argv)
{
    this->_partitionFile = nullptr;
    this->_tfidfFile = nullptr;
    this->_distance = nullptr;
}

SilhouetteProcessor::~SilhouetteProcessor()
{
    delete this->_distance;
}

char* SilhouetteProcessor::process_internal()
{
    PartitionData* part = this->_treader.readFromFile(this->_partitionFile);
    if (part == nullptr)
        part = this->_nreader.readFromFile(this->_partitionFile);
    AbstractPointsSpace* space = this->_spaceReader.readPointSpaceFromFile(this->_tfidfFile);
    SilhouetteIndex sil(this->_distance);
    double index = sil.count(part, space);
    std::cerr << "Silhouette " << index <<std::endl;
    delete part;
    delete space;
    char * buffer = new char[100];
    std::snprintf(
                buffer,
                sizeof(buffer),
                "SILHOUETTE %.4f\n",
                index);
    return buffer;
}

void SilhouetteProcessor::parse()
{
    if (this->_argc < 6)
        throw "too few args fro rand";
    for(unsigned i = 1; i < this->_argc; i++ )
    {
        if (!strcmp(this->_argv[i], "-partition"))
            this->_partitionFile = this->_argv[i+1];
        else if (!strcmp(this->_argv[i], "-tfidf"))
            this->_tfidfFile = this->_argv[i+1];
        else if (!strcmp(this->_argv[i], "-dcos"))
            this->_distance = new CosineDistance();
        else if (!strcmp(this->_argv[i], "-deuc"))
            this->_distance = new EuclideanDistance();
        else if (!strcmp(this->_argv[i], "-dham"))
            this->_distance = new HamiltonDistance();
        else if (!strcmp(this->_argv[i], "-dman"))
            this->_distance = new ManhattanDistance();
    }
}

