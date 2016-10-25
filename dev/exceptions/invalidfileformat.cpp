#include "invalidfileformat.h"

InvalidFileFormat::InvalidFileFormat(const char *file, int line) :
    _data("File being read by AbstractDataReader contains data in invalid format", file, line)
{
}

InvalidFileFormat::InvalidFileFormat(const char *msg, const char *file, int line) :
    _data(msg, file, line)
{
}

InvalidFileFormat::~InvalidFileFormat()
{
}

const char *InvalidFileFormat::what() const throw()
{
    return this->_data.what();
}

