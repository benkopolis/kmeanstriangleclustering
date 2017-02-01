#ifndef STOPWORDSMANAGER_H
#define STOPWORDSMANAGER_H

#include <unordered_map>
#include <utility>
#include <fstream>

#include "stopwordsdetector.h"
#include "commons/hashtable.h"

class StopWordsManager
{
public:
    StopWordsManager(double minimalVariation, double minimalDocFreqPerc);
    virtual ~StopWordsManager();

    void add_word(std::string word, size_t hash, unsigned docId);

    void finalize_statistics(unsigned docNumber, const char *statsFile);
    void finalize_statistics(unsigned docNumber);

    void store_stopwords(std::ofstream& out);

    bool is_stopword(size_t hash) const;

    inline unsigned stopwords_count() const { return this->_sw_num; }

private:

    double _minVariation;
    double _minDocFreqPerc;
    unsigned _sw_num;
    std::unordered_map<std::size_t, StopWordDetector*> * _stopWords;
//    Hashtable<std::size_t, StopWordDetector*> * _stopWords;
};

#endif // STOPWORDSMANAGER_H
