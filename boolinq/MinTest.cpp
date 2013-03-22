#include <vector>
#include <string>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "IterRange.h"
#include "Min.h"

using namespace boolinq;

TEST(Min, ThreeInts)
{
    std::vector<int> src;
    src.push_back(1);
    src.push_back(2);
    src.push_back(3);

    auto rng = range(src);

    EXPECT_EQ(1, min(rng));
    EXPECT_EQ(3, min(rng,[](int a){return -a;}));
}

TEST(Min, FiveStrings)
{
    std::vector<std::string> src;
    src.push_back("hell");
    src.push_back("apple");
    src.push_back("zip");

    auto rng = range(src);

    EXPECT_EQ("apple",  min(rng));
    EXPECT_EQ("zip",  min(rng,[](const std::string & s){return s.size();}));
}
