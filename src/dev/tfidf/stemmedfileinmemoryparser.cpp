#include "stemmedfileinmemoryparser.h"
#include <QTextStream>
#include <QtCore/qmath.h>
#include <QFile>
//#include <QMap>

StemmedFileInMemoryParser::StemmedFileInMemoryParser():
    _nextCoord(0)
{
}

StemmedFileInMemoryParser::~StemmedFileInMemoryParser()
{
    foreach(unsigned int key, _wordsCountPerDocument.keys())
    {
        delete _wordsCountPerDocument[key];
        _wordsCountPerDocument[key] = 0;
    }
}

bool StemmedFileInMemoryParser::fillWithData(QString fileName)
{
    QFile stemmedFile(fileName);
    if(!stemmedFile.open(QFile::ReadOnly))
        return false;
    QTextStream in(&stemmedFile);
    unsigned int docNumber = 0;
    while(!in.atEnd())
    {
        QString line = in.readLine(), tmp;
        QTextStream inner(&line);
        unsigned int lineLen = 0;
        inner >> tmp;
        QHash<uint, unsigned int> *doc = new QHash<uint, unsigned int>();
        QHash<uint, bool> alreadyInserted;
        while(!inner.atEnd())
        {
            inner >> tmp;
            ++lineLen;
            uint hash = qHash(tmp);
            if(!_wordsToCoords.contains(hash))
                _wordsToCoords.insert(hash, _nextCoord++);
            if(!doc->contains(hash))
                doc->insert(hash, 1);
            else
                (*doc)[hash] += 1;
            if(!_globalWordsCount.contains(hash))
                _globalWordsCount.insert(hash, 1);
            else
                _globalWordsCount[hash] += 1;
            if(!alreadyInserted.contains(hash))
            {
                alreadyInserted.insert(hash, true);
                if(!_numberOfDocumentsWithGivenWords.contains(hash))
                    _numberOfDocumentsWithGivenWords.insert(hash, 1);
                else
                    _numberOfDocumentsWithGivenWords[hash] += 1;
            }
        }
        int docIndex = docNumber++;
        _docsLens.insert(docIndex, lineLen);
        _wordsCountPerDocument.insert(docIndex, doc);
    }
    stemmedFile.close();
    return true;
}

double StemmedFileInMemoryParser::tfidf(uint word, unsigned int docIndex)
{
    return tf(word, docIndex) * idf(word);
}

double StemmedFileInMemoryParser::tf(uint word, unsigned int docIndex)
{
    return ((double)(*_wordsCountPerDocument[docIndex])[word] /
            (double)_docsLens[docIndex]);
}

double StemmedFileInMemoryParser::idf(uint word)
{
    return (qLn((double)_wordsCountPerDocument.keys().size() /
                (double)_numberOfDocumentsWithGivenWords[word]));
}

bool StemmedFileInMemoryParser::countTfidfAndStoreInFile(QString fileName)
{
    QFile tfidfFile(fileName);
    if(!tfidfFile.open(QFile::WriteOnly))
        return false;
    QTextStream out(&tfidfFile);
    out << _wordsCountPerDocument.keys().size() << " "
           << _nextCoord << endl;
    foreach(unsigned int docIndex, _wordsCountPerDocument.keys())
    { // for all docs
        foreach(uint word, _wordsCountPerDocument[docIndex]->keys())
        { // for all words in doc - counting tfidf
            double tfidfOfWord = this->tfidf(word, docIndex);
            unsigned int coordsIndex = _wordsToCoords[word];
            out << coordsIndex << ':' << tfidfOfWord << ' ';
        }
        out << endl;
    }
    out.flush();
    tfidfFile.close();
}

bool StemmedFileInMemoryParser::countKeyWordsTfidfAndStoreInFile(QString fileName)
{
    QFile tfidfFile(fileName);
    if(!tfidfFile.open(QFile::WriteOnly))
        return false;
    QTextStream out(&tfidfFile);
    out << _wordsCountPerDocument.keys().size() << " "
           << _nextCoord << endl;

    foreach(unsigned int docIndex, _wordsCountPerDocument.keys())
    { // for all docs - removing words that are not considered as keywords
        if(_wordsCountPerDocument[docIndex]->values().size() == 0)
            continue;
        QList<unsigned int> vals =_wordsCountPerDocument[docIndex]->values();
        qSort(vals);
        int numOfItemsToConsider = 1 + (vals.size() / 5);
        QList<uint> wordsToRemove;
        for(int i = 0; i<vals.size()-numOfItemsToConsider; ++i)
            wordsToRemove.append(_wordsCountPerDocument[docIndex]->key(vals.at(i)));
        foreach(uint word, wordsToRemove)
        {
            unsigned int numOfOccurences = (*_wordsCountPerDocument[docIndex])[word];
            _globalWordsCount[word] -= numOfOccurences;
            _docsLens[docIndex] -= numOfOccurences;
            _wordsCountPerDocument[docIndex]->remove(word);
        }
    }
    foreach(unsigned int docIndex, _wordsCountPerDocument.keys())
    { // for all docs
        foreach(uint word, _wordsCountPerDocument[docIndex]->keys())
        { // for key words in doc - counting tfidf
            double tfidfOfWord = this->tfidf(word, docIndex);
            unsigned int coordsIndex = _wordsToCoords[word];
            out << coordsIndex << ':' << tfidfOfWord << ' ';
        }
        out << endl;
    }
    out.flush();
    tfidfFile.close();
}
