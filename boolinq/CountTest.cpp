#include <list>
#include <vector>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "IterRange.h"
#include "WhereRange.h"
#include "Count.h"

using namespace boolinq;

TEST(Count, ThreeIntsVector)
{
    std::vector<int> src;
    src.push_back(1);
    src.push_back(2);
    src.push_back(3);

    auto rng = range(src);
    
    EXPECT_EQ(3, count(rng));
}

TEST(Count, ThreeIntsList)
{
    std::list<int> src;
    src.push_back(1);
    src.push_back(2);
    src.push_back(3);

    auto rng = range(src);

    EXPECT_EQ(3, count(rng));
}

TEST(Count, FiveInts)
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

    EXPECT_EQ(2, count(dst0));
    EXPECT_EQ(3, count(dst1));
}

TEST(Count, OddCount)
{
    std::vector<int> src;
    src.push_back(1);
    src.push_back(0);
    src.push_back(1);
    src.push_back(0);
    src.push_back(1);

    auto rng = range(src);
    
    EXPECT_EQ(2, count(rng,0));
    EXPECT_EQ(3, count(rng,1));
}
