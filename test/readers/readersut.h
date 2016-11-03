#ifndef NORMALIZEDFORMATDATAREADERUT_H
#define NORMALIZEDFORMATDATAREADERUT_H

#include <UnitTest++/UnitTestPP.h>
#include <iostream>

class ReadersUTHelper
{
public:
    ReadersUTHelper();
    ~ReadersUTHelper();

    std::istream* getFullDataStream();
    std::istream* getNormalizedDataStream();
    std::istream* getEmptyStream();
    std::istream* getFullDataInvalidStream();
    std::istream* getNormalizedDataInvalidStream();

    void initialize();

private:

    static bool _initialized;
};



#endif // NORMALIZEDFORMATDATAREADERUT_H
