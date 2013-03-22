#include <vector>
#include <string>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "IterRange.h"
#include "Any.h"

using namespace boolinq;

TEST(Any, ThreeInts)
{
    std::vector<int> src;
    src.push_back(1);
    src.push_back(2);
    src.push_back(3);

    auto rng = range(src);

    EXPECT_TRUE(any(rng));

    EXPECT_TRUE(any(rng,[](int a){return a==1;}));
    EXPECT_TRUE(any(rng,[](int a){return a==2;}));
    EXPECT_TRUE(any(rng,[](int a){return a==3;}));
    EXPECT_TRUE(any(rng,[](int a){return a>1;}));
    EXPECT_TRUE(any(rng,[](int a){return a<3;}));
    EXPECT_TRUE(any(rng,[](int a){return a!=2;}));

    EXPECT_FALSE(any(rng,[](int a){return a==0;}));
    EXPECT_FALSE(any(rng,[](int a){return a==4;}));
    EXPECT_FALSE(any(rng,[](int a){return a<1;}));
    EXPECT_FALSE(any(rng,[](int a){return a>3;}));
}