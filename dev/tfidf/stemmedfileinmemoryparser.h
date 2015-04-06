#ifndef STEMMEDFILEINMEMORYPARSER_H
#define STEMMEDFILEINMEMORYPARSER_H

#include <QHash>
#include <QString>

class StemmedFileInMemoryParser
{
public:
    StemmedFileInMemoryParser();

    virtual ~StemmedFileInMemoryParser();

    bool fillWithData(QString fileName);

    bool countTfidfAndStoreInFile(QString fileName);

    bool countKeyWordsTfidfAndStoreInFile(QString fileName);



protected:

    double tfidf(uint word, unsigned int docIndex);
    double tf(uint word, unsigned int docIndex);
    double idf(uint word);

    unsigned int _nextCoord;
    QHash<uint, unsigned int> _wordsToCoords;
    QHash<unsigned int, uint> _coordsToWords;
    QHash<uint, unsigned int> _globalWordsCount;
    QHash<unsigned int, unsigned int> _docsLens;
    QHash<uint, unsigned int> _numberOfDocumentsWithGivenWords;
    QHash<unsigned int, QHash<uint, unsigned int>* > _wordsCountPerDocument;
};

#endif // STEMMEDFILEINMEMORYPARSER_H
