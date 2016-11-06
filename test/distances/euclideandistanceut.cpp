#include <UnitTest++/UnitTestPP.h>

#include "commons/testpoint.h"
#include "distances/euclideandistance.h"

SUITE(EuclideanDistanceUT)
{
    TEST(EuclideanDistEmpty)
    {
    }

    TEST(EuclideanDist4)
    {
        TestPoint p0(0, 0, 0);
        TestPoint p1(1, 0, 4);
        EuclideanDistance distance;
        double dist = distance.distance(&p0, &p1);
        CHECK(4 == dist);
    }

    TEST(EuclideanDist0)
    {
        TestPoint p0(0, 0, 0);
        TestPoint p1(1, 0, 0);
        EuclideanDistance distance;
        double dist = distance.distance(&p0, &p1);
        CHECK(0 == dist);
    }

    TEST(EuclideanDist22)
    {
        TestPoint p0(0, 1, 1);
        TestPoint p1(1, 3, 3);
        EuclideanDistance distance;
        double dist = distance.distance(&p0, &p1);
        CHECK_CLOSE(sqrt(8), dist, 0.000000000000001);
    }
}
