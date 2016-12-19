#include "commons/hashtable.h"

#include <UnitTest++/UnitTestPP.h>

SUITE(HashtableUT)
{
    TEST(EmptyHashtable)
    {
        CHECK(true);
    }

    TEST(Hashtable100)
    {
        Hashtable<int, int> test(100);
        for(int i = 0; i < 100; ++i)
        {
            test.insert(i, i);
        }

        for(int i = 0; i < 100; ++i)
        {
            CHECK(i == test[i]);
        }
    }

    TEST(Hashtable100_2)
    {
        Hashtable<int, int> test(1000);
        for(int i = 0; i < 100; ++i)
        {
            test.insert(i, i);
        }

        for(int i = 0; i < 100; ++i)
        {
            CHECK(i == test[i]);
        }
    }

    TEST(HashtableIterator)
    {
        Hashtable<int, int> test(100);
        for(int i = 0; i < 100; ++i)
        {
            test.insert(i, i);
        }

        auto it = test.begin();
        int i = 0;
        int sum = 0;
        while(it != test.end())
        {
            sum += it->second;
            ++it;
        }

        CHECK(495 == sum);
    }

    TEST(HashtableIterator_2)
    {
        Hashtable<int, int> test(1000);
        for(int i = 0; i < 100; ++i)
        {
            test.insert(i, i);
        }

        auto it = test.begin();
        int i = 0;
        int sum = 0;
        while(it != test.end())
        {
            sum += it->second;
            ++it;
        }

        CHECK(495 == sum);
    }
}
