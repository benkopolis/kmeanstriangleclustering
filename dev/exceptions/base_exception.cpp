#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <execinfo.h>

#include "base_exception.h"

base_exception::base_exception(const char *message, const char *file, int line) :
    _bufferSize(10),
    _stackBuffer(0),
    _stackTrace(0)
{
    try
    {
        this->_stackBuffer = (void**)malloc(sizeof(void*) * this->_bufferSize);
        this->_bufferSize = backtrace(this->_stackBuffer, this->_bufferSize);
        if (this->_bufferSize > 0)
            this->_stackTrace = backtrace_symbols(this->_stackBuffer, this->_bufferSize);
        int stackSize = 0;
        if(this->_stackTrace != NULL)
        {
            for(int i = 0; i < this->_bufferSize; ++i)
            {
                stackSize += strlen(this->_stackTrace[i]);
            }
        }
        else
            this->_bufferSize = 0;

        int stackTraceStringSize = stackSize + (3 * this->_bufferSize);
        size_t len = strlen(message) + strlen(file) + 28 + stackTraceStringSize;
        this->_message = new char [len];
        if(this->_stackTrace != NULL)
        {
            sprintf(this->_message, "%s (%s at %d line).\nStackTrace:\r\n", message, file, line);
            int offset = 0, pointer = stackTraceStringSize;
            for(int i = 0; i < this->_bufferSize; ++i)
            {
                offset = len - pointer;
                pointer -= strlen(this->_stackTrace[i]);
                sprintf(this->_message + sizeof(char) * offset, " %s\r\n", this->_stackTrace[i]);
            }
        }
        else
            sprintf(this->_message, "%s (%s at %d line).", message, file, line);
    }
    catch(...)
    {
        this->_message = 0;
        std::cerr << "ERR:" << message << " in file " << file << " at " << line << std::endl;
    }
}

base_exception::~base_exception()
{
    delete [] this->_message;
    if (this->_stackBuffer)
        free(this->_stackBuffer);
    if(this->_stackTrace)
        free(this->_stackTrace);
}

const char *base_exception::what() const throw()
{
    return this->getMessage();
}

const char *base_exception::getMessage() const throw()
{
    if (this->_message == 0)
        return "Uknown exception";
    else
        return this->_message;
}
