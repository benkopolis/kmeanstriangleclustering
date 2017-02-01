#include "stopwordsmanager.h"

#include "commons/logger.h"
#include "commons/globals.h"

StopWordsManager::StopWordsManager(double minimalVariation, double minimalDocFreqPerc) :
    _minVariation(minimalVariation),
    _minDocFreqPerc(minimalDocFreqPerc),
    _sw_num(0)
{
    this->_stopWords = new std::unordered_map<size_t, StopWordDetector*>(Globals::MAX_UNIQUE_WORDS);
//    this->_stopWords = new Hashtable<size_t, StopWordDetector*>(Globals::MAX_UNIQUE_WORDS);
}

StopWordsManager::~StopWordsManager()
{
    delete this->_stopWords;
}

void StopWordsManager::add_word(std::string word, size_t hash, unsigned docId)
{
    if (this->_stopWords->count(hash) > 0)
    {
        StopWordDetector* detector = this->_stopWords->at(hash);
        if(detector != NULL && detector->is_stopword())
        {
            detector->add_word(docId);
        }
    }
    else
    {
        StopWordDetector* detector = new StopWordDetector(word);
        this->_stopWords->insert({hash, detector});
        detector->add_word(docId);
    }
}

void StopWordsManager::finalize_statistics(unsigned docNumber, const char* statsFile)
{
    std::ofstream stats_out(statsFile, std::ios::out);
    auto it = this->_stopWords->begin();
    while(it != this->_stopWords->end())
    {
        it->second->count(double(docNumber), this->_minVariation, this->_minDocFreqPerc, stats_out);
        if(it->second->is_stopword())
            this->_sw_num += 1;
        ++it;
    }
}

void StopWordsManager::finalize_statistics(unsigned docNumber)
{
    auto it = this->_stopWords->begin();
    while(it != this->_stopWords->end())
    {
        it->second->count(double(docNumber), this->_minVariation, this->_minDocFreqPerc);
        if(it->second->is_stopword())
            this->_sw_num += 1;
        ++it;
    }
}

void StopWordsManager::store_stopwords(std::ofstream &out)
{
    auto it = this->_stopWords->begin();
    char str[100];
    std::sprintf(str, "There is '%d' items in stop words", int(this->_stopWords->size()));
    logger::log(str);
    while(it != this->_stopWords->end())
    {
        if (it->second->is_stopword())
        {
            out << it->second->get_word() << std::endl;
        }
        ++it;
    }
}

bool StopWordsManager::is_stopword(size_t hash) const
{
    if(this->_stopWords->count(hash) > 0)
    {
        const StopWordDetector* detector = this->_stopWords->at(hash);
        if (detector == NULL)
            return false;
        return detector->is_stopword();
    }
    else
        return false;
}

