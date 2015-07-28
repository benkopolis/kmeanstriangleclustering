#ifndef STEMMEDFILEINMEMORYPARSER_H
#define STEMMEDFILEINMEMORYPARSER_H

#include <unordered_map>
#include <list>
#include <QString>

class StemmedFileInMemoryParser
{
public:
    StemmedFileInMemoryParser();

    virtual ~StemmedFileInMemoryParser();

    bool fillWithData(QString fileName);

    void countTfidf();

    bool storeTfidfInFile(QString fileName);

protected:

    double tfidf(uint word, unsigned int docIndex);
    double tf(uint word, unsigned int docIndex);
    double idf(uint word);

    unsigned int _nextCoord;
    double minimalValue;
    double quant;
    std::unordered_map<uint, unsigned int> _wordsToCoords;
    std::unordered_map<unsigned int, uint> _coordsToWords;
    std::unordered_map<uint, unsigned int> _globalWordsCount;
    std::unordered_map<unsigned int, unsigned int> _docsLens;
    std::unordered_map<uint, unsigned int> _numberOfDocumentsWithGivenWords;
    std::unordered_map<unsigned int, std::unordered_map<uint, unsigned int>* > _wordsCountPerDocument;
    std::list<std::unordered_map<unsigned, double>*> tfIdfResults;

    static double MinimalValueLowerBound;

};

#endif // STEMMEDFILEINMEMORYPARSER_H
