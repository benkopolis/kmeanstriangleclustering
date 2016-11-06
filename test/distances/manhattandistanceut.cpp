#include <UnitTest++/UnitTestPP.h>
#include <utility>

#include "commons/sparsepoint.h"
#include "distances/manhattandistance.h"

SUITE(ManhattanDistanceUT)
{
    TEST(ManhattanEmpty)
    {
    }

    TEST(ManhattanDistance1)
    {
        SparsePoint p0(0);
        p0.insert(0, 1);
        p0.insert(1, 1);
        SparsePoint p1(1);
        p1.insert(0, 1);
        p1.insert(1, 2);
        ManhattanDistance distance;
        double dist = distance.distance(&p0, &p1);
        CHECK(dist == 0);
    }

    TEST(ManhattanDistance0)
    {
        SparsePoint p0(0);
        p0.insert(0, 1);
        p0.insert(1, 1);
        SparsePoint p1(1);
        p1.insert(0, 1);
        p1.insert(1, 1);
        ManhattanDistance distance;
        double dist = distance.distance(&p0, &p1);
        CHECK(dist == 0);
    }

    TEST(ManhattanDistance2)
    {
        SparsePoint p0(0);
        p0.insert(0, 1);
        p0.insert(1, 1);
        SparsePoint p1(1);
        p1.insert(2, 1);
        p1.insert(3, 2);
        ManhattanDistance distance;
        double dist = distance.distance(&p0, &p1);
        CHECK(dist == 4);
    }
}
