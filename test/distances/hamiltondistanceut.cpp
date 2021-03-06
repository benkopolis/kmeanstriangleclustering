#include <UnitTest++/UnitTestPP.h>
#include <utility>

#include "commons/sparsepoint.h"
#include "distances/hamiltondistance.h"

SUITE(HamiltonDistanceUT)
{
    TEST(HamiltonEmpty)
    {
    }

    TEST(HamiltonDistance1)
    {
        SparsePoint p0(0);
        p0.insert(0, 1);
        p0.insert(1, 1);
        SparsePoint p1(1);
        p1.insert(0, 1);
        p1.insert(1, 2);
        HamiltonDistance distance;
        double dist = distance.distance(&p0, &p1);
        CHECK(dist == 1);
    }

    TEST(HamiltonDistance0)
    {
        SparsePoint p0(0);
        p0.insert(0, 1);
        p0.insert(1, 1);
        SparsePoint p1(1);
        p1.insert(0, 1);
        p1.insert(1, 1);
        HamiltonDistance distance;
        double dist = distance.distance(&p0, &p1);
        CHECK(dist == 0);
    }

    TEST(HamiltonDistance2)
    {
        SparsePoint p0(0);
        p0.insert(0, 1);
        p0.insert(1, 1);
        SparsePoint p1(1);
        p1.insert(2, 1);
        p1.insert(3, 2);
        HamiltonDistance distance;
        double dist = distance.distance(&p0, &p1);
        CHECK(dist == 5);
    }
}
