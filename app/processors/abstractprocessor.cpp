#include "abstractprocessor.h"

#include <string>
#include <cstdio>
#include <iostream>
#include <errno.h>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>

#include "commons/logger.h"

AbstractProcessor::AbstractProcessor(int argc, char **argv)
{
    this->_argc = argc;
    this->_argv = argv;
    logger::log("abstract processor ctor");
    for (int i = 0; i < argc; i = i + 2)
    {
        if (!strcmp(argv[i], "-pipe"))
            this->_pipeName = argv[i+1];
    }

    if (!this->_pipeName.empty())
    {
        logger::log(this->_pipeName.c_str());
        if ((this->_pipe = open(this->_pipeName.c_str(), O_WRONLY|O_NONBLOCK)) < 0)
        {
           std::cerr << std::strerror(errno) << std::endl;
           throw std::strerror(errno);
        }
    }
    logger::log("abstract processor ctor END");
}

AbstractProcessor::~AbstractProcessor()
{
    close(this->_pipe);
}

void AbstractProcessor::put_message(char *msg)
{
    if (msg == nullptr)
        return;
    int num = 0;
    if ((num = write(this->_pipe, msg, std::strlen(msg)+1)) < 0)
    {
        std::cerr << "ERROR: " << strerror(errno) << std::endl;
    }
}

void AbstractProcessor::process()
{
    logger::log("abstract processor parse");
    this->parse();
    logger::log("abstract processor process internal");
    char* message = this->process_internal();
    logger::log(message);
    //logger::log("abstract processor put message");
    //this->put_message(message);
    logger::log("abstract processor clean");
    delete message;
}
