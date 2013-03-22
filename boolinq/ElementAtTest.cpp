#include <vector>
#include <string>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "IterRange.h"
#include "ElementAt.h"

using namespace boolinq;

TEST(ElementAt, ThreeInts)
{
    std::vector<int> src;
    src.push_back(1);
    src.push_back(2);
    src.push_back(3);

    auto rng = range(src);

    EXPECT_EQ(1, elementAt(rng,0));
    EXPECT_EQ(2, elementAt(rng,1));
    EXPECT_EQ(3, elementAt(rng,2));
}

TEST(ElementAt, FiveStrings)
{
    std::vector<std::string> src;
    src.push_back("hello");
    src.push_back("apple");
    src.push_back("nokia");
    src.push_back("oracle");
    src.push_back("ponny");

    auto rng = range(src);

    EXPECT_EQ("hello",  elementAt(rng,0));
    EXPECT_EQ("apple",  elementAt(rng,1));
    EXPECT_EQ("nokia",  elementAt(rng,2));
    EXPECT_EQ("oracle", elementAt(rng,3));
    EXPECT_EQ("ponny",  elementAt(rng,4));
}