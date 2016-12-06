#ifndef STOPWORDSGROUP_H
#define STOPWORDSGROUP_H

#include <string>
#include <list>

class StopWordDetector
{
public:
    StopWordDetector(std::string word);

    inline double get_mean() const throw() { return this->_mean; }
    inline std::string get_word() const throw() { return this->_word; }
    inline bool get_status() const throw() { return this->_status; }

    void add_word(unsigned occurences);

private:

    double _mean;
    unsigned _docs;
    std::string _word;
    bool _status;

};

#endif // STOPWORDSGROUP_H
