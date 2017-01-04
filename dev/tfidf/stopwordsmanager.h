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
    StopWordsManager(double changeFactor);
    virtual ~StopWordsManager();

    void add_word(std::string word, size_t hash, unsigned docId);

    void finalize_statistics(unsigned docNumber);

    void store_stopwords(std::ofstream& out);

    bool is_stopword(size_t hash) const;

private:

    double _changeRatio;
    std::unordered_map<std::size_t, StopWordDetector*> * _stopWords;
//    Hashtable<std::size_t, StopWordDetector*> * _stopWords;
};

#endif // STOPWORDSMANAGER_H
