#include "sequencegenerator.h"

SequenceGenerator::SequenceGenerator() :
    current(0)
{

}

unsigned SequenceGenerator::operator ()()
{
    return current++;
}
