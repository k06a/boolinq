#include <list>
#include <deque>
#include <vector>

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "CommonTests.h"

#include "IterRange.h"
#include "ToContainer.h"

using namespace boolinq;

//////////////////////////////////////////////////////////////////////////

TEST(ToContainer, Array2List)
{
    int src[] = {100,200,300};

    auto rng = range(src);
    auto dst = toContainer<std::list>(rng);

    EXPECT_EQ(3, dst.size());
    EXPECT_EQ(100, dst.front()); dst.pop_front();
    EXPECT_EQ(200, dst.front()); dst.pop_front();
    EXPECT_EQ(300, dst.front()); dst.pop_front();
}

TEST(ToContainer, Array2Deque)
{
    int src[] = {100,200,300};

    auto rng = range(src);
    auto dst = toContainer<std::deque>(rng);

    EXPECT_EQ(3, dst.size());
    EXPECT_EQ(100, dst.front()); dst.pop_front();
    EXPECT_EQ(200, dst.front()); dst.pop_front();
    EXPECT_EQ(300, dst.front()); dst.pop_front();
}

TEST(ToContainer, Array2Vector)
{
    int src[] = {100,200,300};

    auto rng = range(src);
    auto dst = toContainer<std::vector>(rng);

    EXPECT_EQ(3, dst.size());
    EXPECT_EQ(100, dst[0]);
    EXPECT_EQ(200, dst[1]);
    EXPECT_EQ(300, dst[2]);
}

//////////////////////////////////////////////////////////////////////////

TEST(ToContainer, List2List)
{
    std::list<int> src;
    src.push_back(100);
    src.push_back(200);
    src.push_back(300);

    auto rng = range(src);
    auto dst = toContainer<std::list>(rng);

    EXPECT_EQ(dst,src);
}

TEST(ToContainer, Deque2Deque)
{
    std::deque<int> src;
    src.push_back(100);
    src.push_back(200);
    src.push_back(300);

    auto rng = range(src);
    auto dst = toContainer<std::deque>(rng);

    EXPECT_EQ(dst,src);
}

TEST(ToContainer, Vector2Vector)
{
    std::vector<int> src;
    src.push_back(100);
    src.push_back(200);
    src.push_back(300);

    auto rng = range(src);
    auto dst = toContainer<std::vector>(rng);

    EXPECT_EQ(dst,src);
}

//////////////////////////////////////////////////////////////////////////
