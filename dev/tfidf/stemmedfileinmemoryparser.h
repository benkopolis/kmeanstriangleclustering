#ifndef STEMMEDFILEINMEMORYPARSER_H
#define STEMMEDFILEINMEMORYPARSER_H

#include <string>
#include <functional>
#include <list>
#include <vector>
#include <unordered_map>

#include "stopwordsmanager.h"
#include "stopwordsdict.h"

struct LoadDataArgs
{
    double docFreqPerc;
    double changeRatio;
    const char *fileName;
    const char *stopWordsStore;
    const char *stopWordsDict;

    LoadDataArgs()
    {
        this->fileName = NULL;
        this->stopWordsDict = NULL;
        this->stopWordsStore = NULL;
        this->changeRatio = 0;
        this->docFreqPerc = 0;
    }
};

class StemmedFileInMemoryParser
{
public:
    StemmedFileInMemoryParser();

    virtual ~StemmedFileInMemoryParser();

    bool loadData(const LoadDataArgs& args);

    void countTfidf();

    bool storeTfidfInFile(const char* fileName);

    inline std::list<std::unordered_map<unsigned, double>*>& getTfIdfResults() { return this->tfIdfResults; }
    inline std::vector<std::string>& getFileIds() { return this->_fileIds; }

    std::string get_terms() const;

protected:

    double tfidf(std::size_t word, unsigned int docIndex);
    double tf(std::size_t word, unsigned int docIndex);
    double idf(std::size_t word);

    unsigned int _nextCoord;
    double minimalValue;
    double quant;
    std::vector<std::string> _fileIds;
    std::unordered_map<unsigned int, std::string> _coordsToRealWords;
    std::unordered_map<std::size_t, unsigned int> _wordsToCoords;
    std::unordered_map<unsigned int, std::size_t> _coordsToWords;
    std::unordered_map<std::size_t, unsigned int> _globalWordsCount;
    std::unordered_map<unsigned int, unsigned int> _docsLens;
    std::unordered_map<std::size_t, unsigned int> _numberOfDocumentsWithGivenWords;
    std::unordered_map<unsigned int, std::unordered_map<std::size_t, unsigned int>* > _wordsCountPerDocument;
    std::list<std::unordered_map<unsigned, double>*> tfIdfResults;

    std::hash<std::string> hash_fn;
    StopWordsManager* _swManager;
    StopWordsDict* _stopWordsDict;

    static double MinimalValueLowerBound;

};

#endif // STEMMEDFILEINMEMORYPARSER_H
