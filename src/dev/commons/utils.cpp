#include "utils.h"

Utils *Utils::instance = 0;

Utils::Utils()
{
}

Utils *Utils::getInstance()
{
    if(Utils::instance == 0)
        Utils::instance = new Utils();
    return Utils::instance;
}
