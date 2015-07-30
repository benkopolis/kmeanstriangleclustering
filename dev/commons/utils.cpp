#include "utils.h"

Utils *Utils::instance = 0;

Utils::Utils() : messages(0)
{
}

Utils::~Utils()
{
}

Utils *Utils::getInstance()
{
    if(Utils::instance == 0)
        Utils::instance = new Utils();
    return Utils::instance;
}

void Utils::destroy()
{
    if(instance == 0)
        return;
    delete instance;
    instance = 0;
}

const char *Utils::concatenate(const char *one, const char *two)
{
    std::unique_ptr<std::string> str(new std::string(one));
    str->append(two);
    this->messages.push_back(std::move(str));
    return this->messages.back()->data();
}
