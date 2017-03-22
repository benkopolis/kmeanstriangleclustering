#ifndef ABSTRACTPROCESSOR_H
#define ABSTRACTPROCESSOR_H

#include <unordered_map>
#include <list>
#include <cstring>
#include <string>

class AbstractProcessor
{
protected:
    AbstractProcessor(int argc, char** argv);

    std::unordered_map<std::string, std::string> _params;
    int _argc;
    char** _argv;
    std::string _pipeName;
    int _pipe;


    virtual void parse() = 0;
    virtual char* process_internal() = 0;
    void put_message(char* msg);

public:

    virtual ~AbstractProcessor();
    void process();

};

#endif // ABSTRACTPROCESSOR_H
