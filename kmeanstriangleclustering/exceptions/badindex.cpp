#include "badindex.h"

BadIndex::BadIndex()
{
}

BadIndex::~BadIndex()
{

}

const char *BadIndex::what() const
{
    return "Given index is out of range";
}
