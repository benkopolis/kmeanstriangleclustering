#include "stemmedfileparsercontroller.h"
#include "tfidf/tfidfhistogramgenerator.h"

#include <QByteArray>

StemmedFileParserController::StemmedFileParserController(QObject *parent)
    : QObject(parent), parser(0)
{
}

StemmedFileParserController::~StemmedFileParserController()
{
    delete this->parser;
}

void StemmedFileParserController::onRead(const QString &in)
{
    this->parser = new StemmedFileInMemoryParser();
    QByteArray ba = in.toLatin1();
    emit readDone(this->parser->fillWithData(ba.data()));
}

void StemmedFileParserController::onProcess()
{
    this->parser->countTfidf();
    emit processDone();
}

void StemmedFileParserController::onWrite(const QString &out)
{
    QByteArray ba = out.toLatin1();
    emit writeDone(this->parser->storeTfidfInFile(ba.data()));
}

void StemmedFileParserController::onGenerateHistograms(const QString &out)
{
    TfidfHistogramGenerator generator;
    generator.generateHistograms(this->parser->getTfIdfResults());
    QByteArray ba = out.toLatin1();
    try {
        generator.save(ba.data());
    } catch(IOException& e) {
        emit generateHistogramsDone(false, e.what());
        return;
    }

    emit generateHistogramsDone(true, "");
}

