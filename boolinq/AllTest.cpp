#include <vector>
#include <string>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "IterRange.h"
#include "All.h"

using namespace boolinq;

TEST(All, ThreeInts)
{
    std::vector<int> src;
    src.push_back(1);
    src.push_back(2);
    src.push_back(3);

    auto rng = range(src);

    EXPECT_TRUE(all(rng));
    
    EXPECT_TRUE(all(rng,[](int a){return a>0;}));
    EXPECT_TRUE(all(rng,[](int a){return a<4;}));
    EXPECT_TRUE(all(rng,[](int a){return a>0 && a<4;}));

    EXPECT_FALSE(all(rng,[](int a){return a>2;}));
    EXPECT_FALSE(all(rng,[](int a){return a==1;}));
    EXPECT_FALSE(all(rng,[](int a){return a<3;}));
}

TEST(All, ThreeIntsSecond)
{
    std::vector<int> src;
    src.push_back(0);
    src.push_back(1);
    src.push_back(2);

    auto rng = range(src);

    EXPECT_FALSE(all(rng));
    
    EXPECT_TRUE(all(rng,[](int a){return a>=0;}));
    EXPECT_TRUE(all(rng,[](int a){return a<=2;}));
    EXPECT_TRUE(all(rng,[](int a){return a>=0 && a<=2;}));

    EXPECT_FALSE(all(rng,[](int a){return a>1;}));
    EXPECT_FALSE(all(rng,[](int a){return a==1;}));
    EXPECT_FALSE(all(rng,[](int a){return a<2;}));
}