#ifndef STEMMEDFILEINMEMORYPARSER_H
#define STEMMEDFILEINMEMORYPARSER_H

#include <string>
#include <functional>
#include <list>
#include <vector>
#include <unordered_map>

#include "stopwordsmanager.h"

class StemmedFileInMemoryParser
{
public:
    StemmedFileInMemoryParser();

    virtual ~StemmedFileInMemoryParser();

    bool loadData(const char* fileName, const char* stopWordsDict, double changeRatio);

    void countTfidf();

    bool storeStopWords(const char *fileName);

    bool storeTfidfInFile(const char* fileName);

    inline std::list<std::unordered_map<unsigned, double>*>& getTfIdfResults() { return this->tfIdfResults; }
    inline std::vector<std::string>& getFileIds() { return this->_fileIds; }

protected:

    double tfidf(std::size_t word, unsigned int docIndex);
    double tf(std::size_t word, unsigned int docIndex);
    double idf(std::size_t word);

    unsigned int _nextCoord;
    double minimalValue;
    double quant;
    std::vector<std::string> _fileIds;
    std::unordered_map<std::size_t, unsigned int> _wordsToCoords;
    std::unordered_map<unsigned int, std::size_t> _coordsToWords;
    std::unordered_map<std::size_t, unsigned int> _globalWordsCount;
    std::unordered_map<unsigned int, unsigned int> _docsLens;
    std::unordered_map<std::size_t, unsigned int> _numberOfDocumentsWithGivenWords;
    std::unordered_map<unsigned int, std::unordered_map<std::size_t, unsigned int>* > _wordsCountPerDocument;
    std::list<std::unordered_map<unsigned, double>*> tfIdfResults;

    std::hash<std::string> hash_fn;
    StopWordsManager* _swManager;

    static double MinimalValueLowerBound;

};

#endif // STEMMEDFILEINMEMORYPARSER_H
