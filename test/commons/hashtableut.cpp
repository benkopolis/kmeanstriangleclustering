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

        CHECK(4950 == sum);
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

        CHECK(4950 == sum);
    }

    TEST(HashtableIteratorReverse)
    {
        Hashtable<int, int> test(100);
        for(int i = 0; i < 100; ++i)
        {
            test.insert(i, i);
        }

        auto it = test.end();
        int i = 0;
        int sum = 0;
        do
        {
            --it;
            sum += it->second;
        }
        while(it != test.begin());

        CHECK(4950 == sum);
    }

    TEST(HashtableIteratorReverse_2)
    {
        Hashtable<int, int> test(1000);
        for(int i = 0; i < 100; ++i)
        {
            test.insert(i, i);
        }

        auto it = test.end();
        int i = 0;
        int sum = 0;
        do
        {
            --it;
            sum += it->second;
        }
        while(it != test.begin());

        CHECK(4950 == sum);
    }

    TEST(HashtableContains)
    {
        Hashtable<size_t, size_t> test(100);
        CHECK(!test.contains(1));
        CHECK(!test.contains(2));
        CHECK(!test.contains(57));
        for(unsigned i = 0; i < 100; ++i)
        {
            test.insert(i, i);
            CHECK(test.size() == i + 1);
        }

        CHECK(test.contains(0));
        CHECK(test.contains(10));
        CHECK(test.contains(57));
        CHECK(!test.contains(101));
    }

    TEST(HashtableFind)
    {
        Hashtable<int, int> test(100);
        CHECK(test.find(2) == test.end());
        CHECK(test.find(45) == test.end());
        CHECK(test.find(98) == test.end());
        for(int i = 0; i < 100; ++i)
        {
            test.insert(i, i);
        }

        CHECK(test.find(0) != test.end());
        CHECK(test.find(10) != test.end());
        CHECK(test.find(57) != test.end());
        CHECK(test.find(101) == test.end());
    }
}
