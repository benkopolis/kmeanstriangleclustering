#ifndef SEQUENTIALCENTERSPICKER_H
#define SEQUENTIALCENTERSPICKER_H

#include "abstractcenterspicker.h"

template<class PointType>
class SequentialCentersPicker : public AbstractCentersPicker<PointType>
{
public:
    SequentialCentersPicker() {}

    virtual PartitionData *performInitialPartition(unsigned clusters, AbstractPointsSpace<PointType>* ps)
    {
        PartitionData *data = new PartitionData(clusters, ps->getDeclaredNumPoints());
        this->initialData = new CentersData(clusters);
        unsigned cid;
        for (unsigned pid = 0; pid < ps->getDeclaredNumPoints(); pid++)
        {
            cid = pid % clusters;
            data->assign_unsafe(pid, cid);
            this->addCoordsToCenter(ps->getPoint(pid), cid);
        }

        this->divideCentersCoords(data);
        return data;
    }
};

#endif // SEQUENTIALCENTERSPICKER_H
