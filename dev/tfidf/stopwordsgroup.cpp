#include "stopwordsgroup.h"

#include <cmath>

StopWordDetector::StopWordDetector(std::string word):
    _mean(0),
    _docs(0),
    _status(true)
{
}

void StopWordDetector::add_word(unsigned occurences)
{
    if (this->_docs == 0)
        this->_mean = double(occurences);
    else
    {
        double old_mean = this->_mean;
        this->_mean = (this->_mean + (double(occurences) / double(this->_docs))) / (1.0 + (1.0 / double(this->_docs)));
        double delta = fabs(this->_mean - old_mean) / old_mean;
        if (delta >= 0.2)
            this->_status = false;
    }

    this->_docs += 1;
}

