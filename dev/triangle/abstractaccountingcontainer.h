#ifndef ABSTRACTACCOUNTINGCONTAINER_H
#define ABSTRACTACCOUNTINGCONTAINER_H

#include <QThread>
#include "models.hpp"

class AbstractAccountingContainer : QThread
{
public:

    virtual void update(const QVector<Distance>& delta) = 0;

protected:

        AbstractAccountingContainer();

        virtual void run() {}

};

#endif // ABSTRACTACCOUNTINGCONTAINER_H
