#include "tfidfhistogramgenerator.h"
#include "exceptions/ioexception.h"
#include "readers/normalizedformatdatareader.h"

#include <cfloat>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

TfidfHistogramGenerator::TfidfHistogramGenerator():
    quant(DBL_MAX)
{

}

TfidfHistogramGenerator::~TfidfHistogramGenerator()
{

}

void TfidfHistogramGenerator::generateHistograms(const std::list<std::unordered_map<unsigned, double>*> &tfIdfData)
{
    for(const std::unordered_map<unsigned, double>* vec: tfIdfData)
    {
        if(this->nonZeroCoordsFrequency.count(vec->size() == 0))
            this->nonZeroCoordsFrequency.insert({vec->size(), 1});
        else
            this->nonZeroCoordsFrequency[vec->size()] += 1;
        for(const std::pair<unsigned, double>& pair : *vec)
        {
            if(this->quant > pair.second) // should be bigger then DBL_MIN times 5
                this->quant = pair.second;
            if(this->coordsValuesFrequency.count(pair.second) == 0)
                this->coordsValuesFrequency.insert({pair.second, 1});
            else
                this->coordsValuesFrequency[pair.second] += 1;
        }
    }
}

void TfidfHistogramGenerator::generateHistograms(const char *tfidfFileName) throw(IOException)
{
    std::ifstream in(tfidfFileName, std::ios::in);
    if(!in.is_open())
        throw IOException(Utils::getInstance()->concatenate(tfidfFileName, " can't be open to read."));
    NormalizedFormatDataReader reader;
    AbstractPointsSpace<SparsePoint> * space = reader.parseFile(&in);
    for(unsigned i = 0; i < space->getNumPoints(); ++i) {
        PtrCAbstractPoint p = space->getPoint(i);
        if(this->nonZeroCoordsFrequency.count(p->size()) == 0)
            this->nonZeroCoordsFrequency.insert({p->size(), 1});
        else
            this->nonZeroCoordsFrequency[p->size()] += 1;
        for(unsigned key: p->getKeys()) {
            if(this->coordsValuesFrequency.count((*p)[key]) == 0)
                this->coordsValuesFrequency.insert({(*p)[key], 1});
            else
                this->coordsValuesFrequency[(*p)[key]] += 1;
        }
    }

    this->quant = space->getQuant();
    delete space;
}

void TfidfHistogramGenerator::save(const char *histogramsFileName) throw(IOException)
{
    this->saveCoords(Utils::getInstance()->concatenate(histogramsFileName, ".chist"));
    this->saveDims(Utils::getInstance()->concatenate(histogramsFileName, ".dhist"));
}

void TfidfHistogramGenerator::saveCoords(const char *fileName) throw(IOException)
{
    std::ofstream out(fileName, std::ios::out | std::ios::trunc);
    if(!out.is_open())
        throw IOException(Utils::getInstance()->concatenate(fileName, " can't be open to write."));
    for(std::pair<double, unsigned> pair: this->coordsValuesFrequency) {
        out << pair.first << " " << pair.second << std::endl;
    }
    out.flush();
    out.close();
}

void TfidfHistogramGenerator::saveDims(const char *fileName) throw(IOException)
{
    std::ofstream out(fileName, std::ios::out | std::ios::trunc);
    if(!out.is_open())
        throw IOException(Utils::getInstance()->concatenate(fileName, " can't be open to write."));
    for(std::pair<unsigned, unsigned> pair: this->nonZeroCoordsFrequency) {
        out << pair.first << " " << pair.second << std::endl;
    }
    out.flush();
    out.close();
}

