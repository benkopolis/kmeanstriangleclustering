
#include "commons/logger.h"
#include "exceptions/ioexception.h"
#include "stemmedfileinmemoryparser.h"
#include "stopwordsmanager.h"

#include <algorithm>
#include <cmath>
#include <cfloat>
#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <sstream>

//#include <QMap>
/// We don't care for DBL_MIN, so quantization has to be at 2*DBL_MIN,
/// so smallest values have to be 4*DBL_MIN, so minimal value has to be bigger
/// than that.
double StemmedFileInMemoryParser::MinimalValueLowerBound = DBL_MIN * 5;

StemmedFileInMemoryParser::StemmedFileInMemoryParser():
    _nextCoord(0),
    minimalValue(DBL_MAX),
    _swManager(NULL),
    _stopWordsDict(NULL)
{
}

StemmedFileInMemoryParser::~StemmedFileInMemoryParser()
{
    for(auto pair : this->_wordsCountPerDocument)
    {
        delete pair.second;
        pair.second = 0;
    }

    for(auto map : this->tfIdfResults)
    {
        delete map;
        map = 0;
    }
}

void split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss;
    ss.str(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
}


std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

bool StemmedFileInMemoryParser::loadData(const LoadDataArgs &args)
{
    std::ifstream in(args.fileName, std::ios::in);
    if (args.stopWordsDict != NULL)
    {
        logger::log("Reading stop words dict");
        this->_stopWordsDict = new StopWordsDict();
        this->_stopWordsDict->load(args.stopWordsDict);
    }
    else if (args.stopWordsStore != NULL)
    {
        logger::log("Creating stop words manager");
        this->_swManager = new StopWordsManager(args.changeRatio, args.docFreqPerc);
    }
    if(!in.is_open())
        return false;
    unsigned docNumber = 0;
    logger::log("Before big loop");
    while(!in.eof())
    {
        std::string docId;
        std::string line;
        std::getline(in, line); // reading a document - there is one per line
        if(line.empty())
            continue;
        std::transform(line.begin(), line.end(), line.begin(), ::tolower);
        std::istringstream inner(line);
        inner >> docId; // reading the 'docId:' thingy
        docId = docId.substr(0, docId.length() - 1);
        this->_fileIds.push_back(docId);
        unsigned int lineLen = 0;
        std::unordered_map<size_t, unsigned int>* doc = new std::unordered_map<size_t, unsigned int>();
        std::unordered_map<size_t, bool> alreadyInserted;
        while(!inner.eof()) // reading words from document
        {
            std::string word;
            inner >> word;
            if(word.empty())
                continue;
            ++lineLen;
            size_t hash = this->hash_fn(word);
            if (this->_stopWordsDict != NULL && this->_stopWordsDict->contains(hash))
                continue; // skip stop words if loaded to memory
            else if (this->_swManager != NULL)
                this->_swManager->add_word(word, hash, docNumber);

            if(this->_wordsToCoords.count(hash) < 1)
            {
                this->_wordsToCoords.insert({hash, this->_nextCoord});
                this->_coordsToRealWords.insert({this->_nextCoord, word});
                this->_nextCoord += 1;
            }
            if(doc->count(hash) == 0)
                doc->insert({hash, 1});
            else
                (*doc)[hash] += 1;
            if(this->_globalWordsCount.count(hash) > 0)
                this->_globalWordsCount.insert({hash, 1});
            else
                this->_globalWordsCount[hash] += 1;
            if(alreadyInserted.count(hash) == 0)
            {
                alreadyInserted.insert({hash, true});
                if(this->_numberOfDocumentsWithGivenWords.count(hash) == 0)
                    this->_numberOfDocumentsWithGivenWords.insert({hash, 1});
                else
                    this->_numberOfDocumentsWithGivenWords[hash] += 1;
            }
        }

        this->_docsLens.insert({docNumber, lineLen});
        this->_wordsCountPerDocument.insert({docNumber, doc});
        ++docNumber;
    }
    in.close();

    if(this->_swManager != NULL)
    {
        logger::log("Opening sw stream with some words");
        std::ofstream outsw(args.stopWordsStore, std::ios::out);
        if (outsw.is_open() == false)
            throw IOException("Can not open stopWords file to wrtie\n", __FILE__, __LINE__);
        logger::log("finalizing stats");
        this->_swManager->finalize_statistics(this->_docsLens.size());
        this->_swManager->store_stopwords(outsw);
        char buffer[100];
        std::snprintf(buffer, sizeof(buffer), "There is '%d' stopwords", this->_swManager->stopwords_count());
        logger::log(buffer, __LINE__, __FILE__);
    }

    return true;
}

double StemmedFileInMemoryParser::tfidf(size_t word, unsigned int docIndex)
{
    return tf(word, docIndex) * idf(word);
}

double StemmedFileInMemoryParser::tf(size_t word, unsigned int docIndex)
{
    return (double)(*_wordsCountPerDocument[docIndex])[word] /
           (double)_docsLens[docIndex];
}

double StemmedFileInMemoryParser::idf(size_t word)
{
    return log((double)_wordsCountPerDocument.size() /
                (double)_numberOfDocumentsWithGivenWords[word]);
}

void StemmedFileInMemoryParser::countTfidf()
{
    for(auto wordPerDocPair : this->_wordsCountPerDocument)
    { // for all docs
        std::unordered_map<unsigned, double>* map = new std::unordered_map<unsigned, double>();
        std::unordered_map<std::size_t, unsigned>* doc = wordPerDocPair.second;
        for(auto word : *(doc))
        { // for all words in doc - counting tfidf
            double tfidfOfWord = this->tfidf(word.first, wordPerDocPair.first);
            if(tfidfOfWord < this->minimalValue && tfidfOfWord > MinimalValueLowerBound)
                this->minimalValue = tfidfOfWord;
            unsigned coordsIndex = this->_wordsToCoords[word.first];
            map->insert({coordsIndex, tfidfOfWord});
        }
        this->tfIdfResults.push_back(map);
    }
    this->quant = this->minimalValue / 4;
}

bool StemmedFileInMemoryParser::storeTfidfInFile(const char *fileName)
{
    std::ofstream out(fileName, std::ios::trunc | std::ios::out);
    if(!out.is_open())
        return false;
    out << this->_wordsCountPerDocument.size() << " "
        << this->_nextCoord << " " << this->quant << std::endl; // header format: <number of vectors> <number of dimensions> <quantization value>
    unsigned index = 0;
    for(auto map : this->tfIdfResults)
    { // for all docs
        out << this->_fileIds[index] << ' '; // printing file id
        ++index;
        for(auto pair : *map)
        { // for all words in doc - counting tfidf
            if(pair.second < DBL_MIN)
                pair.second = this->minimalValue / 2;
            out << pair.first << ':' << pair.second << ' ';
        }
        out << std::endl;
    }
    out << std::ends;
    out.flush();
    out.close();
    char buffer[100];
    std::snprintf(buffer, sizeof(buffer), "There is '%d' terms", this->_nextCoord);
    logger::log(buffer, __LINE__, __FILE__);
    return true;
}

std::string StemmedFileInMemoryParser::get_terms() const
{
    std::string str;
    std::ostringstream oss(str);
    oss << std::endl;
    for(auto pair : this->_coordsToRealWords)
    {
        oss << pair.first << " : " << pair.second << std::endl;
    }

    return str;
}
