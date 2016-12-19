#include <UnitTest++/UnitTestPP.h>

#include "tfidf/stemmedfileinmemoryparser.h"

SUITE(StemmedParserUT)
{
    TEST(EmptyStemmed)
    {
        CHECK(true);
    }

    TEST(StemmedParserUT)
    {
        StemmedFileInMemoryParser parser;
        parser.loadData("stemmed_test.txt", NULL, 0);
        parser.countTfidf();
        std::list<std::unordered_map<unsigned, double>*>& result = parser.getTfIdfResults();
        std::vector<std::string>& fileIds = parser.getFileIds();
        CHECK(result.size() == fileIds.size());
        parser.storeTfidfInFile("stemmed_test.tfidf");
    }
}
