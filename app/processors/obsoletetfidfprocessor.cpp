#include "obsoletetfidfprocessor.h"

#include "commons/logger.h"

ObsoleteTfIdfProcessor::ObsoleteTfIdfProcessor(int argc, char **argv)
    : AbstractProcessor(argc, argv)
{
    this->_stemFile = nullptr;
    this->_stopOut = nullptr;
    this->_stopIn = nullptr;
    this->_tfidfFile = nullptr;
    this->_stopStats = nullptr;
    this->_ratio = 0;
    this->_docfreq = 0;
    logger::log("Created parser");
}

ObsoleteTfIdfProcessor::~ObsoleteTfIdfProcessor()
{

}

void ObsoleteTfIdfProcessor::parse()
{
    if (this->_argc < 3) // invalid
        throw "Not enough arguments";
    for(unsigned i = 1; i < this->_argc; i += 2)
    {
        if (!strcmp(this->_argv[i], "-stem"))
            this->_stemFile = this->_argv[i+1];
        else if (!strcmp(this->_argv[i], "-stop"))
            this->_stopOut = this->_argv[i+1];
        else if (!strcmp(this->_argv[i], "-stop_stats"))
            this->_stopStats = this->_argv[i+1];
        else if (!strcmp(this->_argv[i], "-istop"))
            this->_stopIn = this->_argv[i+1];
        else if(!strcmp(this->_argv[i], "-tfidf"))
            this->_tfidfFile = this->_argv[i+1];
        else if(!strcmp(this->_argv[i], "-min_variation"))
            this->_ratio = atof(this->_argv[i+1]);
        else if(!strcmp(this->_argv[i], "-min_docfreq"))
            this->_docfreq = atof(this->_argv[i+1]);
    }
    logger::log("Assigned names - going to load data");
}

char *ObsoleteTfIdfProcessor::process_internal()
{
    LoadDataArgs args;
    args.changeRatio = this->_ratio;
    args.fileName = this->_stemFile;
    args.stopWordsDict = this->_stopIn;
    args.docFreqPerc = this->_docfreq;
    logger::log("Loading data");
    this->_parser.loadData(args);
    if (this->_stopOut != nullptr)
    {
        logger::log("Stroing stop wrods");
        this->_parser.storeStopWords(this->_stopOut, this->_stopStats);
    }
    logger::log("Counting tfidf");
    this->_parser.countTfidf();
    logger::log("Storing data");
    this->_parser.storeTfidfInFile(this->_tfidfFile);
    logger::log("Getting terms", __LINE__, __FILE__);
    char * buffer = new char[10];
    std::snprintf(
                buffer,
                sizeof(buffer),
                "TERMS\n");
    return buffer;
}

