#ifndef NORMALIZEDFORMATDATAREADERUT_H
#define NORMALIZEDFORMATDATAREADERUT_H

#include <QtTest/QtTest>
#include "readers/fulldatareader.h"
#include "readers/normalizedformatdatareader.h"

class ReadersUT : public QObject
{
    Q_OBJECT
public:
    explicit ReadersUT(QObject *parent = 0);
    ~ReadersUT();

signals:

private slots:

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
