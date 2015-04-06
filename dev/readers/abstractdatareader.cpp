#include "abstractdatareader.h"

template<typename T>
AbstractDataReader<T>::AbstractDataReader()
{
}

template<typename T>
AbstractPointsSpace<T> *AbstractDataReader<T>::readPointSpaceFromFile(QString fileName)
{
    QFile file(fileName);
    QTextStream *in;
    if(file.open(QFile::ReadOnly))
        in = new QTextStream(&file);
    else
    {
        QTextStream err(stderr);
        err << "Can not open file for reading: " << fileName;
        return 0;
    }
    return parseFile(in);
}
