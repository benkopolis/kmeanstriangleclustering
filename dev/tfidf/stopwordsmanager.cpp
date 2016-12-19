#include "stopwordsmanager.h"

#include "commons/globals.h"

StopWordsManager::StopWordsManager(double changeFactor) :
    _changeRatio(changeFactor)
{
//    this->_stopWords = new std::unordered_map<size_t, StopWordDetector*>(Globals::MAX_UNIQUE_WORDS);
    this->_stopWords = new Hashtable<size_t, StopWordDetector*>(Globals::MAX_UNIQUE_WORDS);
}

StopWordsManager::~StopWordsManager()
{
    delete this->_stopWords;
}

void StopWordsManager::add_word(std::string word, size_t hash, unsigned docId)
{
    if (this->_stopWords->contains(hash))
    {
        StopWordDetector* detector = this->_stopWords->at(hash);
        if(detector != NULL && detector->is_stopword())
        {
            detector->add_word(docId);
//            if (!detector->get_status())
//            {
//                delete detector;
//                this->_stopWords[hash] = 0;
//            }
        }
    }
    else
    {
        StopWordDetector* detector = new StopWordDetector(word);
        this->_stopWords->insert({hash, detector});
        detector->add_word(docId);
    }
}

void StopWordsManager::finalize_statistics(unsigned docNumber)
{
    auto it = this->_stopWords->begin();
    while(it != this->_stopWords->end())
    {
        it->second->count(double(docNumber), this->_changeRatio);
        ++it;
    }
}

void StopWordsManager::store_stopwords(std::ofstream &out)
{
    auto it = this->_stopWords->begin();
    while(it != this->_stopWords->end())
    {
        if (it->second->is_stopword())
        {
            out << it->second->get_word() << std::endl;
        }
    }
}

bool StopWordsManager::is_stopword(size_t hash) const
{
    if(this->_stopWords->contains(hash))
    {
        const StopWordDetector* detector = this->_stopWords->at(hash);
        if (detector == NULL)
            return false;
        return detector->is_stopword();
    }
    else
        return false;
}

