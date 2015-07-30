#ifndef STEMMEDFILEPARSERCONTROLLER_H
#define STEMMEDFILEPARSERCONTROLLER_H

#include <QObject>
#include "tfidf/stemmedfileinmemoryparser.h"

class StemmedFileParserController : public QObject
{
    Q_OBJECT
public:
    explicit StemmedFileParserController(QObject *parent = 0);
    ~StemmedFileParserController();

signals:

    void readDone(bool ok);
    void processDone();
    void writeDone(bool ok);
    void generateHistogramsDone(bool ok, const QString& message);

public slots:

    void onRead(const QString& in);
    void onProcess();
    void onWrite(const QString& out);
    void onGenerateHistograms(const QString& out);

private:

    StemmedFileInMemoryParser* parser;
};

#endif // STEMMEDFILEPARSERCONTROLLER_H
