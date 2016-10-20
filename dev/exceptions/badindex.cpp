#include "badindex.h"

BadIndex::BadIndex(const char *file, int line) :
    _data("Given index is out of range", file, line)
{
}

BadIndex::BadIndex(const char * msg, const char *file, int line) :
    _data(msg, file, line)
{
}

const char *BadIndex::what() const throw()
{
    return this->_data.what();
}
