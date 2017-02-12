#include <UnitTest++/UnitTestPP.h>
#include <iostream>

#include "analysis/variationofinformationindex.h"

SUITE(VariationOfInformationIndexTests)
{
    TEST(EmptyVar)
    {
        CHECK(true);
    }

    TEST(BestVariation)
    {
        PartitionData* one = new PartitionData(3, 9);
        PartitionData* two = new PartitionData(3, 9);
        one->assign_unsafe(0, 0);
        one->assign_unsafe(1, 0);
        one->assign_unsafe(2, 0);
        one->assign_unsafe(3, 1);
        one->assign_unsafe(4, 1);
        one->assign_unsafe(5, 1);
        one->assign_unsafe(6, 2);
        one->assign_unsafe(7, 2);
        one->assign_unsafe(8, 2);
        two->assign_unsafe(0, 0);
        two->assign_unsafe(1, 0);
        two->assign_unsafe(2, 0);
        two->assign_unsafe(3, 1);
        two->assign_unsafe(4, 1);
        two->assign_unsafe(5, 1);
        two->assign_unsafe(6, 2);
        two->assign_unsafe(7, 2);
        two->assign_unsafe(8, 2);

        VariationOfInformationIndex index;
        double val = index.count(one, two);
        std::cout << "Var: " << val << std::endl;
    }

    TEST(WorstVariation)
    {
        PartitionData* one = new PartitionData(3, 9);
        PartitionData* two = new PartitionData(3, 9);
        one->assign_unsafe(0, 0);
        one->assign_unsafe(1, 0);
        one->assign_unsafe(2, 0);
        one->assign_unsafe(3, 1);
        one->assign_unsafe(4, 1);
        one->assign_unsafe(5, 1);
        one->assign_unsafe(6, 2);
        one->assign_unsafe(7, 2);
        one->assign_unsafe(8, 2);
        two->assign_unsafe(0, 0);
        two->assign_unsafe(1, 1);
        two->assign_unsafe(2, 2);
        two->assign_unsafe(3, 0);
        two->assign_unsafe(4, 1);
        two->assign_unsafe(5, 2);
        two->assign_unsafe(6, 0);
        two->assign_unsafe(7, 1);
        two->assign_unsafe(8, 2);

        VariationOfInformationIndex index;
        double val = index.count(one, two);
        std::cout << "Var: " << val << std::endl;
    }
}

