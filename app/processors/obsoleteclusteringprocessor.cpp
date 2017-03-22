#include "obsoleteclusteringprocessor.h"
#include "commons/globals.h"
#include "algorithms/kmeansalgorithm.h"
#include "analysis/randindex.h"

#include "distances/cosinedistance.h"
#include "distances/euclideandistance.h"
#include "distances/hamiltondistance.h"
#include "distances/manhattandistance.h"
#include "pickers/randomcenterpicker.h"
#include "pickers/dimensionbasedcenterspicker.h"
#include "pickers/graphcentersandclusterspicker.h"
#include "pickers/sequentialcenterspicker.h"

#include <cstring>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <iostream>

ObsoleteClusteringProcessor::ObsoleteClusteringProcessor(int argc, char** argv)
    : AbstractProcessor(argc, argv)
{
    this->_distance = nullptr;
    this->_picker = nullptr;
    this->_resFile = nullptr;
    this->_tfidfFile = nullptr;
    this->_clusters = 10;
    this->_iterations = 25;
}

ObsoleteClusteringProcessor::~ObsoleteClusteringProcessor()
{
    delete this->_distance;
    delete this->_picker;
}

char* ObsoleteClusteringProcessor::process_internal()
{
    AbstractPointsSpace * space = this->_reader.readPointSpaceFromFile(this->_tfidfFile);
    /* Init DensePoint keys */
    Globals::DIMENSIONS = space->getNumDimensions();
    DensePoint::InitializeKeys(Globals::DIMENSIONS);
    /* Construct grouping algo */
    KMeansAlgorithm<SparsePoint> * algo =
            new KMeansAlgorithm<SparsePoint>(
                this->_distance,
                this->_picker,
                space,
                this->_clusters,
                this->_iterations);
    algo->execute();
    std::cout << "Iterations: " << algo->getNumberOfIterations();
    const PartitionData* partData = algo->getPartitionData();
    partData->printClustersTransposed(this->_resFile);
    PartitionData* original = space->convertTo(this->_clusters);
    RandIndex rand_proc;
    double rand = rand_proc.count(partData, original);
    unsigned iterationsNumber = algo->getNumberOfIterations();
    std::cout << "Rand index: " << rand << std::endl;
    std::cerr << "KMeansCorrectDataRandomPickerCosineDist " << iterationsNumber << std::endl;
    char * buffer = new char[100];
    std::snprintf(
                buffer,
                sizeof(buffer),
                "RANDINDEX %.4f\n ITERATIONS %d",
                rand,
                iterationsNumber);
    delete space;
    delete algo;
    return buffer;
}

void ObsoleteClusteringProcessor::parse()
{
    if (this->_argc < 6)
        std::cerr << "Too few arguments to cluster!!!" << std::endl;
    for(unsigned i = 1; i < this->_argc; ++i)
    {
        if (!strcmp(this->_argv[i], "-input"))
            this->_tfidfFile = this->_argv[i+1];
        else if (!strcmp(this->_argv[i], "-out"))
            this->_resFile = this->_argv[i+1];
        else if (!strcmp(this->_argv[i], "-rand"))
            this->_picker = new RandomCenterPicker<SparsePoint>();
        else if (!strcmp(this->_argv[i], "-seq"))
            this->_picker = new SequentialCentersPicker<SparsePoint>();
        else if (!strcmp(this->_argv[i], "-dim"))
            this->_picker = new DimensionBasedCentersPicker<SparsePoint>();
        else if (!strcmp(this->_argv[i], "-graph"))
            this->_picker = new GraphCentersAndClustersPicker<SparsePoint>();
        else if (!strcmp(this->_argv[i], "-iter"))
            this->_iterations = std::strtoul(this->_argv[i+1], nullptr, 0);
        else if (!strcmp(this->_argv[i], "-clusters"))
            this->_clusters = std::strtoul(this->_argv[i+1], nullptr, 0);
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

