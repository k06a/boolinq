#include <vector>
#include <string>

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "CommonTests.h"

#include "IterRange.h"
#include "SkipRange.h"

using namespace boolinq;

//////////////////////////////////////////////////////////////////////////

TEST(SkipRange, ManyToMany)
{
    int src[] = {1,2,3,4,5,6};
    int ans[] = {1,2,3,4,5,6};

    auto rng = range(src);
    auto dst = skip(rng, 0);

    CheckRangeEqArray(dst, ans);
}

TEST(SkipRange, ManyToLess)
{
    int src[] = {1,2,3,4,5,6};
    int ans[] = {4,5,6};

    auto rng = range(src);
    auto dst = skip(rng, 3);

    CheckRangeEqArray(dst, ans);
}

TEST(SkipRange, ManyToOne)
{
    int src[] = {1,2,3,4,5,6};
    int ans[] = {6};

    auto rng = range(src);
    auto dst = skip(rng, 5);

    CheckRangeEqArray(dst, ans);
}

TEST(SkipRange, ManyToZero)
{
    int src[] = {1,2,3,4,5,6};

    auto rng = range(src);
    auto dst = skip(rng, 6);

    EXPECT_TRUE(dst.empty());
}

TEST(SkipRange, ManyToZeroLess)
{
    int src[] = {1,2,3,4,5,6};

    auto rng = range(src);
    auto dst = skip(rng, 10);

    EXPECT_TRUE(dst.empty());
}

//////////////////////////////////////////////////////////////////////////

TEST(SkipRange, OneToOne)
{
    int src[] = {5};
    int ans[] = {5};

    auto rng = range(src);
    auto dst = skip(rng, 0);

    CheckRangeEqArray(dst, ans);
}

TEST(SkipRange, OneToZero)
{
    int src[] = {5};

    auto rng = range(src);
    auto dst = skip(rng, 1);

    EXPECT_TRUE(dst.empty());
}

TEST(SkipRange, OneToZeroLess)
{
    int src[] = {5};

    auto rng = range(src);
    auto dst = skip(rng, 2);

    EXPECT_TRUE(dst.empty());
}

TEST(SkipRange, ZeroToZero)
{
    std::vector<int> src;

    auto rng = range(src);
    auto dst = skip(rng, 0);

    EXPECT_TRUE(rng.empty());
}

TEST(SkipRange, ZeroToZeroLess)
{
    std::vector<int> src;

    auto rng = range(src);
    auto dst = skip(rng, 2);

    EXPECT_TRUE(rng.empty());
}

//////////////////////////////////////////////////////////////////////////
