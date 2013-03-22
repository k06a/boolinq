#include <vector>
#include <string>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "IterRange.h"
#include "Max.h"

using namespace boolinq;

TEST(Max, ThreeInts)
{
    std::vector<int> src;
    src.push_back(1);
    src.push_back(2);
    src.push_back(3);

    auto rng = range(src);

    EXPECT_EQ(3, max(rng));
    EXPECT_EQ(1, max(rng,[](int a){return -a;}));
}

TEST(Max, FiveStrings)
{
    std::vector<std::string> src;
    src.push_back("hell");
    src.push_back("apple");
    src.push_back("zip");

    auto rng = range(src);

    EXPECT_EQ("zip",  max(rng));
    EXPECT_EQ("apple", max(rng,[](const std::string s){return s.size();}));
}