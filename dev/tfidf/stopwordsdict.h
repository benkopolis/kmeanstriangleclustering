#ifndef STOPWORDSDICT_H
#define STOPWORDSDICT_H

#include <functional>
#include <string>
#include <unordered_map>

#include "exceptions/ioexception.h"

class StopWordsDict
{
public:
    StopWordsDict();

    void load(const char* fileName) throw(IOException);
    bool contains(size_t hash) const;

private:

    std::hash<std::string> hash_fn;
    std::unordered_map<std::size_t, std::string> _words;

};

#endif // STOPWORDSDICT_H
