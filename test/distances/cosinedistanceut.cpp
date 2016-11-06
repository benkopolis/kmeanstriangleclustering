#include <UnitTest++/UnitTestPP.h>

#include "commons/testpoint.h"
#include "distances/cosinedistance.h"

SUITE(CosineDistanceUT)
{
    TEST(CosineDistEmpty)
    {
    }

    TEST(CosineDistanceCheckCalculations08)
    {
        CosineDistance distance;
        TestPoint p0(0, 0, 4);
        TestPoint p1(1, 3, 4);
        double dist = distance.distance(&p0, &p1);
        CHECK_CLOSE(0.2, dist, 0.000000000000001);
    }

    TEST(CosineDistanceCheckCalculations081)
    {
        CosineDistance distance;
        TestPoint p0(0, 1, 2);
        TestPoint p1(1, 2, 1);
        double dist = distance.distance(&p0, &p1);
        CHECK_CLOSE(0.2, dist, 0.000000000000001);
    }

    TEST(CosineDistanceCheckCalculations1)
    {
        CosineDistance distance;
        TestPoint p0(0, 1, 2);
        TestPoint p1(1, 1, 2);
        double dist = distance.distance(&p0, &p1);
        CHECK_CLOSE(0, dist, 0.000000000000001);
    }
}
