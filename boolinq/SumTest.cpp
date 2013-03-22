#include <list>
#include <vector>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "IterRange.h"
#include "WhereRange.h"
#include "Sum.h"

using namespace boolinq;

TEST(Sum, ThreeInts)
{
    std::vector<int> src;
    src.push_back(1);
    src.push_back(2);
    src.push_back(3);

    auto rng = range(src);

    EXPECT_EQ(6, sum(rng));
}

TEST(Sum, FiveInts)
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

    EXPECT_EQ(6, sum(dst0));
    EXPECT_EQ(9, sum(dst1));
}

TEST(Sum, BoolSum)
{
    std::vector<int> src;
    src.push_back(1);
    src.push_back(2);
    src.push_back(3);
    src.push_back(4);
    src.push_back(5);

    auto rng = range(src);

    EXPECT_EQ(2, sum(rng,[](int a){return a%2 == 0;}));
    EXPECT_EQ(3, sum(rng,[](int a){return a%2 == 1;}));
}

TEST(Sum, FiveStringsLen)
{
    std::vector<std::string> src;
    src.push_back("hello");
    src.push_back("apple");
    src.push_back("nokia");
    src.push_back("oracle");
    src.push_back("ponny");

    auto rng = range(src);

    EXPECT_EQ(26, sum(rng,[](const std::string & str){return str.size();}));
}

TEST(Sum, FiveStringsData)
{
    std::vector<std::string> src;
    src.push_back("hello");
    src.push_back("apple");
    src.push_back("nokia");
    src.push_back("oracle");
    src.push_back("ponny");

    auto rng = range(src);

    std::string ans = "helloapplenokiaoracleponny";

    EXPECT_EQ(ans, sum(rng));
}
