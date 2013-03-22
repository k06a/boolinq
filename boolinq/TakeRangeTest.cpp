#include <vector>
#include <string>

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "CommonTests.h"

#include "IterRange.h"
#include "TakeRange.h"

using namespace boolinq;

//////////////////////////////////////////////////////////////////////////

TEST(TakeRange, ManyToMore)
{
    int src[] = {1,2,3,4,5,6};
    int ans[] = {1,2,3,4,5,6};

    auto rng = range(src);
    auto dst = take(rng, 10);

    CheckRangeEqArray(dst, ans);
}

TEST(TakeRange, ManyToMany)
{
    int src[] = {1,2,3,4,5,6};
    int ans[] = {1,2,3,4,5,6};

    auto rng = range(src);
    auto dst = take(rng, 6);

    CheckRangeEqArray(dst, ans);
}

TEST(TakeRange, ManyToLess)
{
    int src[] = {1,2,3,4,5,6};
    int ans[] = {1,2,3};

    auto rng = range(src);
    auto dst = take(rng, 3);

    CheckRangeEqArray(dst, ans);
}

TEST(TakeRange, ManyToOne)
{
    int src[] = {1,2,3,4,5,6};
    int ans[] = {1};

    auto rng = range(src);
    auto dst = take(rng, 1);

    CheckRangeEqArray(dst, ans);
}

TEST(TakeRange, ManyToZero)
{
    int src[] = {1,2,3,4,5,6};

    auto rng = range(src);
    auto dst = take(rng, 0);

    EXPECT_TRUE(dst.empty());
}

//////////////////////////////////////////////////////////////////////////

TEST(TakeRange, OneToMore)
{
    int src[] = {5};
    int ans[] = {5};

    auto rng = range(src);
    auto dst = take(rng, 5);

    CheckRangeEqArray(dst, ans);
}

TEST(TakeRange, OneToOne)
{
    int src[] = {5};
    int ans[] = {5};

    auto rng = range(src);
    auto dst = take(rng, 1);

    CheckRangeEqArray(dst, ans);
}

TEST(TakeRange, OneToZero)
{
    int src[] = {5};

    auto rng = range(src);
    auto dst = take(rng, 0);

    EXPECT_TRUE(dst.empty());
}

TEST(TakeRange, ZeroToZero)
{
    std::vector<int> src;

    auto rng = range(src);
    auto dst = take(rng, 0);

    EXPECT_TRUE(rng.empty());
}

//////////////////////////////////////////////////////////////////////////
