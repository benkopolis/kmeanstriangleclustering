//file with test executions
#include <iostream>
#include <UnitTest++/UnitTest++.h>
#include <UnitTest++/TestReporterStdout.h>
#include <cstring>

#include "commons/densepointut.h"
#include "commons/sparsepointut.h"
#include "commons/globals.h"


int main(int argc, char** argv)
{
    if (argc > 1)
    {
        const bool bSuite = strcmp("suite", argv[1]) == 0;

        const UnitTest::TestList& allTests(UnitTest::Test::GetTestList());
        UnitTest::TestList selectedTests;
        UnitTest::Test* p = allTests.GetHead();
        bool readersTest = false, densePointTest = false;
        int counter = 0;
        while(p)
        {
            for(int i=1; i< argc; ++i)
            {
                UnitTest::Test* check = p;
                p = p->m_nextTest;

                if(strcmp(bSuite
                          ? check->m_details.suiteName
                          : check->m_details.testName,
                          argv[i]) == 0)
                {
                    if (strcmp(check->m_details.suiteName, "ReadersUT") == 0)
                    {
                        if (densePointTest)
                            continue;
                        readersTest = true;
                    }

                    if (strcmp(check->m_details.suiteName, "DensePointUT") == 0)
                    {
                        if (readersTest)
                            continue;
                        densePointTest = true;
                    }

                    selectedTests.Add(check);
                }
            }
            counter++;
            if(counter > 100)
            {
                std::cerr << "Too many iterations!" << std::endl;
                break;
            }
        }

        if(readersTest)
        {
            Globals::DIMENSIONS = 3;
            DensePoint::InitializeKeys(Globals::DIMENSIONS);
        }
        else
        {
            Globals::DIMENSIONS = 100;
            DensePoint::InitializeKeys(Globals::DIMENSIONS);
        }

        UnitTest::TestReporterStdout reporter;
        UnitTest::TestRunner runner(reporter);
        return runner.RunTestsIf( selectedTests, 0, UnitTest::True(), 0 );
    }
    else
    {

        try
        {
            return UnitTest::RunAllTests();
        }
        catch (std::exception const &b)
        {
            std::cerr << b.what() << std::endl;
        }
    }
}
