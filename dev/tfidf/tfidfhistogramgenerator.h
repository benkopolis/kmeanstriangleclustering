#ifndef TFIDFHISTOGRAMGENERATOR_H
#define TFIDFHISTOGRAMGENERATOR_H

#include "exceptions/ioexception.h"

#include <list>
#include <unordered_map>

class TfidfHistogramGenerator
{
public:
    TfidfHistogramGenerator();
    ~TfidfHistogramGenerator();

    void generateHistograms(const std::list<std::unordered_map<unsigned, double> *> &tfIdfData);
    void generateHistograms(const char* tfidfFileName) throw(IOException);

    void save(const char* histogramsFileName) throw(IOException);

private:

    void saveCoords(const char* fileName) throw(IOException);
    void saveDims(const char* fileName) throw(IOException);

    double quant;

    std::unordered_map<double, unsigned> coordsValuesFrequency;
    std::unordered_map<unsigned, unsigned> nonZeroCoordsFrequency;
};

#endif // TFIDFHISTOGRAMGENERATOR_H
