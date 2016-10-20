#ifndef DENSEPOINTUT_H
#define DENSEPOINTUT_H

#include "commons/densepoint.h"
#include "exceptions/badindex.h"
#include "exceptions/notdensepoint.h"
#include <UnitTest++/UnitTest++.h>

SUITE(DensePointUT)
{
    TEST(CreateAndEvaluateDensePoint)
    {
        DensePoint::InitializeKeys(100);
        DensePoint* point = new DensePoint(1, 100);
        CHECK(point);
        CHECK(1 == point->getPointId());
        CHECK_EQUAL(100, point->getKeys().size());
        CHECK_EQUAL(100, point->size());
        CHECK(!point->contains(101));
        CHECK_THROW((*point)[101], BadIndex);
        CHECK_THROW(point->diff(0, true), NotDensePoint);
        CHECK(!point->diff(0, false));
        delete point;
        point = 0;
    }

    TEST(CompareDensePoints)
    {
        DensePoint::InitializeKeys(100);
        DensePoint* p = new DensePoint(0, 100);
        DensePoint* q = new DensePoint(0, 100);
        for(int i = 0; i < 100; ++i) {
            (*p)[i] = 0.1;
            (*q)[i] = 0.1;
        }

        (*p)[1] = 0.5;
        (*p)[50] = 1;
        (*q)[1] = 0.2;
        (*q)[50] = 0.4;

        CHECK(p->diff(q, true) != 0);
        CHECK(p->diff(q, true) == q->diff(p, true));
    }
}

#endif // DENSEPOINTUT_H
