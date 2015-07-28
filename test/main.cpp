//file with test executions
#include <UnitTest++/UnitTest++.h>
#include "commons/densepointut.h"
#include "commons/sparsepointut.h"
#include "commons/globals.h"


int main(int argc, char** argv)
{
    Globals::DIMENSIONS = 100;
    DensePoint::InitializeKeys(Globals::DIMENSIONS);
    return UnitTest::RunAllTests();
}
