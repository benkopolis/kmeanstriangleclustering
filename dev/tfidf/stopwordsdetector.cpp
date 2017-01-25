  #include "stopwordsdetector.h"
#include "commons/logger.h"

#include <cmath>
#include <cstdio>

StopWordDetector::StopWordDetector(std::string word):
    _docs(0),
    _word(word),
    _is_stopword(true)
{
}

void StopWordDetector::add_word(unsigned docId)
{
    if (this->_docs.size() == 0)
        this->_docs.insert({docId, 1});
    else
    {
        if(this->_docs.count(docId) == 0)
        {
            this->_docs.insert({docId, 1});
        }
        else
        {
            this->_docs[docId] = this->_docs[docId] + 1;
        }
    }
}

void StopWordDetector::count(double docNumber, double minVariation, double minDocFreqPerc)
{
    double mean = 0, variation = 0;
    auto it = this->_docs.begin();
    while(it != this->_docs.end())
    {
        mean = mean + it->second;
        ++it;
    }

    mean = mean / docNumber;
    it = this->_docs.begin();

    while(it != this->_docs.end())
    {
        variation = variation + pow(mean - it->second, 2.0);
        ++it;
    }

    variation = variation / docNumber;
    char buffer[160];
    std::snprintf(
                buffer,
                sizeof(buffer),
                "%s: %.4f < %.4f || ((%d / %d) < %d)",
                this->_word.c_str(),
                variation,
                minVariation,
                int(docNumber),
                int(minDocFreqPerc),
                int(this->_docs.size()));
    logger::log(buffer, __LINE__, __FILE__);
    this->_is_stopword =  variation < minVariation;
}

