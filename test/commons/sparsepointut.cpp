#include "commons/sparsepoint.h"
#include "exceptions/badindex.h"
#include "exceptions/notsparsepoint.h"

#include <UnitTest++/UnitTestPP.h>

SUITE(SparsePointUT)
{
    TEST(EmptySparsePoint)
    {
        CHECK(true);
    }

    TEST(CreateAndEvaluateSparsePoint)
    {
        SparsePoint* sparse = new SparsePoint(10);
        CHECK(sparse->size() == 0);
        CHECK(10 == sparse->getPointId());
        sparse->insert(1, 1.34);
        sparse->insert(5, 0.34533);
        CHECK(sparse->size() == 2);
        CHECK_CLOSE(1.34, (*sparse)[1], 0.00001);
        CHECK_CLOSE(0.34533, (*sparse)[5], 0.00001);
        CHECK_THROW((*sparse)[0], BadIndex);
        CHECK_THROW(sparse->diff(0, false), NotSparsePoint);
        delete sparse;
        sparse = 0;
    }

    TEST(CompareSparsePoints)
    {
        SparsePoint* p = new SparsePoint(0);
        SparsePoint* q = new SparsePoint(0);
        p->insert(1, 1.34);
        p->insert(5, 0.34533);
        q->insert(1, 1);
        q->insert(3, 0.5);

        CHECK(p->diff(q, false) == 1);
        CHECK(q->diff(p, false) == 1);
        CHECK(p->diff(q, true) == 2);
        CHECK(q->diff(p, true) == 2);
        delete p;
        delete q;
        q = 0;
        p = 0;
    }
}
