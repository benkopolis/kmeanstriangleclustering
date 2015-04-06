#include "badindex.h"

BadIndex::BadIndex()
{
}

BadIndex::~BadIndex() throw()
{

}

const char *BadIndex::what() const throw()
{
    return "Given index is out of range";
}
