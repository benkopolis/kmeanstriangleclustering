#ifndef NORMALIZEDFORMATDATAREADERUT_H
#define NORMALIZEDFORMATDATAREADERUT_H

#include "readers/fulldatareader.h"
#include "readers/normalizedformatdatareader.h"

class ReadersUT
{
public:
    ReadersUT();
    ~ReadersUT();

    void testFullDataReader();
    void testFullDataReader_data();
    void testFullDataReaderEmptyStream();
    void testFullDataReaderWrongFormat();
    void testNormalizedDataReader();
    void testNormalizedDataReader_data();
    void testNormalizedDataReaderEmptyStream();
    void testNormalizedDataReaderWrongFormat();
};

#endif // NORMALIZEDFORMATDATAREADERUT_H
