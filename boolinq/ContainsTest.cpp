#include <vector>
#include <string>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "IterRange.h"
#include "Contains.h"

using namespace boolinq;

TEST(Contains, ThreeInts)
{
    std::vector<int> src;
    src.push_back(1);
    src.push_back(2);
    src.push_back(3);

    auto rng = range(src);

    EXPECT_TRUE(contains(rng,1));
    EXPECT_TRUE(contains(rng,2));
    EXPECT_TRUE(contains(rng,3));

    EXPECT_FALSE(contains(rng,0));
    EXPECT_FALSE(contains(rng,4));
}

TEST(Contains, FiveStrings)
{
    std::vector<std::string> src;
    src.push_back("hello");
    src.push_back("apple");
    src.push_back("nokia");
    src.push_back("oracle");
    src.push_back("ponny");

    auto rng = range(src);

    EXPECT_TRUE(contains(rng,"hello"));
    EXPECT_TRUE(contains(rng,"apple"));
    EXPECT_TRUE(contains(rng,"nokia"));
    EXPECT_TRUE(contains(rng,"oracle"));
    EXPECT_TRUE(contains(rng,"ponny"));

    EXPECT_FALSE(contains(rng,"dino"));
    EXPECT_FALSE(contains(rng,"lord"));
}