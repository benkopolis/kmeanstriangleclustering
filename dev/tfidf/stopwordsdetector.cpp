#include "stopwordsdetector.h"

#include <cmath>

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
        //this->_mean = double(occurences);
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

void StopWordDetector::count(double docNumber, double ratio)
{
    double mean = 0, standardDeviation = 0;
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
        standardDeviation = standardDeviation + pow(mean - it->second, 2.0);
        ++it;
    }

    standardDeviation = standardDeviation / docNumber;
    standardDeviation = sqrt(standardDeviation);

    this->_is_stopword = (standardDeviation / mean) > ratio;
}

