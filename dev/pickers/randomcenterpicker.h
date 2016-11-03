#ifndef RANDOMCENTERPICKER_H
#define RANDOMCENTERPICKER_H

#include "abstractcenterspicker.h"
#include "commons/centersdata.h"

template<typename PointType>
class RandomCenterPicker : public AbstractCentersPicker<PointType>
{
public:
    RandomCenterPicker() {}
    virtual PartitionData *performInitialPartition(unsigned clusters, AbstractPointsSpace<PointType>* ps)
    {
        PartitionData* data = new PartitionData(clusters, ps->getDeclaredNumPoints());
        this->initialData = new CentersData(clusters);
        unsigned cid;
        for (unsigned pid = 0; pid < ps->getDeclaredNumPoints(); pid++)
        {
            cid = qrand() % clusters;
            data->assign_unsafe(pid, cid);
            this->addCoordsToCenter(ps->getPoint(pid), cid);
        }

        this->divideCentersCoords(data);

        return data;
    }
};

#endif // RANDOMCENTERPICKER_H
