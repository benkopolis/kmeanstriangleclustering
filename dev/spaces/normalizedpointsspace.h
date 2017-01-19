#ifndef NORMALIZEDPOINTSSPACE_H
#define NORMALIZEDPOINTSSPACE_H

#include "abstractpointsspace.h"
#include "commons/partitiondata.h"
#include "exceptions/invalidconversiontype.h"

#include <string>
#include <typeinfo>
#include <unordered_map>

template<typename T>
class NormalizedPointsSpace : public AbstractPointsSpace<T>
{
public:
    NormalizedPointsSpace(unsigned num_points, unsigned num_dimensions);
    NormalizedPointsSpace(const NormalizedPointsSpace& another);

    virtual ~NormalizedPointsSpace();

    virtual PtrCAbstractPoint operator [](const unsigned& pid) throw(BadIndex);
    virtual PtrCAbstractPoint operator [](const unsigned& pid) const throw(BadIndex);

    virtual void insertPoint(T *p, unsigned index);
    virtual PtrCAbstractPoint getPoint(unsigned index) const;
    virtual bool contains(unsigned index) const;
    virtual unsigned getNumOfInsertedPoints() const;

    virtual void savePointsSpace(const char *fileName);

    PartitionData* convertTo(unsigned clusters) const
    {
        if (this->_convertedTo != nullptr)
            return this->_convertedTo;
        PartitionData* data = new PartitionData(clusters);
        for(auto p: this->points__)
        {
            PtrCAbstractPoint tmp = p.second;
            std::string fileId = tmp->getFileId();
            unsigned clusterId = std::strtoul(fileId.substr(0, 1).c_str(), nullptr, 0);
            data->assign(p.first, clusterId);
        }

        this->_convertedTo = data;
        return data;
    }

protected:

    std::unordered_map<unsigned, PtrCAbstractPoint> points__;
	unsigned int lines__;

private:

    PartitionData* _convertedTo;

};

#include "normalizedpointsspace.cpp"

#endif // NORMALIZEDPOINTSSPACE_H
