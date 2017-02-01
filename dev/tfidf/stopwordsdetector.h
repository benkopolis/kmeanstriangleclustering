#ifndef STOPWORDSGROUP_H
#define STOPWORDSGROUP_H

#include <iostream>
#include <list>
#include <string>
#include <unordered_map>

class StopWordDetector
{
public:
    StopWordDetector(std::string word);


    inline std::string get_word() const throw() { return this->_word; }
    inline bool is_stopword() const throw() { return this->_is_stopword; }

    void add_word(unsigned docId);
    void count(double docNumber, double minVariation, double minDocFreqPerc, std::ofstream &stats);
    void count(double docNumber, double minVariation, double minDocFreqPerc);

private:

    std::unordered_map<unsigned, unsigned> _docs;
    std::string _word;
    bool _is_stopword;

};

#endif // STOPWORDSGROUP_H
