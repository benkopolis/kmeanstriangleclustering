#include "badindex.h"

BadIndex::BadIndex() : message("Given index is out of range")
{
}

BadIndex::BadIndex(const char * msg) : message(msg)
{
}

const char *BadIndex::what() const throw()
{
    return this->message;
}
