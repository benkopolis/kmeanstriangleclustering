#ifndef OBSOLETECLUSTERINGPROCESSOR_H
#define OBSOLETECLUSTERINGPROCESSOR_H

#include "abstractprocessor.h"

#include "distances/abstractdistance.h"
#include "pickers/abstractcenterspicker.h"
#include "readers/normalizedformatdatareader.h"

class ObsoleteClusteringProcessor : public AbstractProcessor
{
public:
    ObsoleteClusteringProcessor(int argc, char **argv);
    virtual ~ObsoleteClusteringProcessor();

protected:

    virtual char* process_internal();
    virtual void parse();

private:

    AbstractDistance* _distance = nullptr;
    AbstractCentersPicker<SparsePoint>* _picker = nullptr;
    NormalizedFormatDataReader _reader;
    char * _resFile = nullptr;
    char * _tfidfFile = nullptr;
    unsigned _clusters = 0;
    unsigned _iterations = 0;
};

#endif // OBSOLETECLUSTERINGPROCESSOR_H
