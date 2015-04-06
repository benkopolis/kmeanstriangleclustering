#include "invalidfileformat.h"

InvalidFileFormat::InvalidFileFormat()
{

}

InvalidFileFormat::~InvalidFileFormat()
{

}

const char *InvalidFileFormat::what() const throw()
{
    return "File being read by AbstractDataReader contains data in invalid format";
}

