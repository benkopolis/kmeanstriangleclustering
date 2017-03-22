#ifndef SILHOUETTEPROCESSOR_H
#define SILHOUETTEPROCESSOR_H

#include "spaces/normalizedpointsspace.h"
#include "commons/partitiondata.h"
#include "distances/abstractdistance.h"
#include "abstractprocessor.h"
#include "readers/normalizedformatdatareader.h"
#include "readers/partitions/transposedpartitionreader.h"
#include "readers/partitions/normalpartitionreader.h"

class SilhouetteProcessor : public AbstractProcessor
{
public:
    SilhouetteProcessor(int argc, char** argv);
    virtual ~SilhouetteProcessor();

protected:

    virtual char* process_internal();
    virtual void parse();

private:

    TransposedPartitionReader _treader;
    NormalPartitionReader _nreader;
    NormalizedFormatDataReader _spaceReader;
    char* _tfidfFile;
    char* _partitionFile;
    AbstractDistance* _distance;
};

#endif // SILHOUETTEPROCESSOR_H
