#include <list>
#include <vector>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "IterRange.h"
#include "WhereRange.h"
#include "Avg.h"

using namespace boolinq;

TEST(Avg, ThreeInts)
{
    std::vector<int> src;
    src.push_back(1);
    src.push_back(2);
    src.push_back(3);

    auto rng = range(src);

    EXPECT_EQ(2, avg(rng));
}

TEST(Avg, FiveInts)
{
    std::vector<int> src;
    src.push_back(1);
    src.push_back(2);
    src.push_back(3);
    src.push_back(4);
    src.push_back(5);

    auto rng = range(src);
    auto dst0 = where(rng, [](int a){return a%2 == 0;});
    auto dst1 = where(rng, [](int a){return a%2 == 1;});

    EXPECT_EQ(3, avg(dst0));
    EXPECT_EQ(3, avg(dst1));
}

TEST(Avg, FiveStringsLen)
{
    std::vector<std::string> src;
    src.push_back("hello");
    src.push_back("apple");
    src.push_back("nokia");
    src.push_back("oracle");
    src.push_back("ponny");

    auto rng = range(src);

    EXPECT_EQ(5, avg(rng,[](const std::string & str){return str.size();}));
}
