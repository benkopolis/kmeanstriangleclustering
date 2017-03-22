#ifndef VARIATIONOFINFORMATIONPROCESSOR_H
#define VARIATIONOFINFORMATIONPROCESSOR_H

#include "abstractprocessor.h"
#include "readers/partitions/transposedpartitionreader.h"
#include "readers/partitions/normalpartitionreader.h"

class VariationOfInformationProcessor : public AbstractProcessor
{
public:
    VariationOfInformationProcessor(int argc, char** argv);

protected:

    virtual char* process_internal();
    virtual void parse();

private:

    TransposedPartitionReader _treader;
    NormalPartitionReader _nreader;
    char* _partOne;
    char* _partTwo;
};

#endif // VARIATIONOFINFORMATIONPROCESSOR_H
