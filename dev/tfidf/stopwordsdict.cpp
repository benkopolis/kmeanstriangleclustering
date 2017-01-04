#include "stopwordsdict.h"

#include <fstream>

StopWordsDict::StopWordsDict()
{

}

void StopWordsDict::load(const char *fileName) throw(IOException)
{
    std::ifstream in(fileName, std::ios::in);
    if(!in.is_open())
        throw IOException("Cannot open file with stop words.", __FILE__, __LINE__);
    std::string w;
    while(!in.eof())
    {
        in >> w;
        std::size_t hash = this->hash_fn(w);
        this->_words.insert({hash, w});
    }
}

bool StopWordsDict::contains(size_t hash) const
{
    return this->_words.count(hash) > 0;
}

