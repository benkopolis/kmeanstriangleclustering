#ifndef TFIDFHISTOGRAMGENERATOR_H
#define TFIDFHISTOGRAMGENERATOR_H

#include <unordered_map>

class TfidfHistogramGenerator
{
public:
    TfidfHistogramGenerator();
    ~TfidfHistogramGenerator();

    void generateHistograms(std::list<const std::unordered_map<unsigned, double>*>& tfIdfData);
    void generateHistograms(const char* tfidfFileName);

private:

    double quant;

    std::unordered_map<double, unsigned> coordsValuesFrequency;
    std::unordered_map<unsigned, unsigned> nonZeroCoordsFrequency;
};

#endif // TFIDFHISTOGRAMGENERATOR_H
