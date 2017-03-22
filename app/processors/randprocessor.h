#ifndef RANDPROCESSOR_H
#define RANDPROCESSOR_H

#include "abstractprocessor.h"
#include "readers/partitions/transposedpartitionreader.h"
#include "readers/partitions/normalpartitionreader.h"

class RandProcessor : public AbstractProcessor
{
public:
    RandProcessor(int argc, char** argv);

protected:

    virtual char* process_internal();
    virtual void parse();

private:

    TransposedPartitionReader _treader;
    NormalPartitionReader _nreader;
    char* _partOne;
    char* _partTwo;
};

#endif // RANDPROCESSOR_H
