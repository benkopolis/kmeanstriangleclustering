#ifndef OBSOLETETFIDFPROCESSOR_H
#define OBSOLETETFIDFPROCESSOR_H

#include "abstractprocessor.h"
#include "tfidf/stemmedfileinmemoryparser.h"

class ObsoleteTfIdfProcessor : public AbstractProcessor
{
public:
    ObsoleteTfIdfProcessor(int argc, char** argv);
    virtual ~ObsoleteTfIdfProcessor();

protected:

    virtual void parse();
    virtual char* process_internal();

private:

    StemmedFileInMemoryParser _parser;
    char* _stemFile;
    char* _stopOut;
    char* _stopIn;
    char* _tfidfFile;
    char* _stopStats;
    double _ratio;
    double _docfreq;
};

#endif // OBSOLETETFIDFPROCESSOR_H
