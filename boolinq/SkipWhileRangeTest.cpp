#include <vector>
#include <string>

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "CommonTests.h"

#include "boolinq.h"

using namespace boolinq;

//////////////////////////////////////////////////////////////////////////

TEST(SkipWhileRange, ManyToMore)
{
    int src[] = {1,2,3,4,5,6};
    int ans[] = {1,2,3,4,5,6};

    auto rng = from(src);
    auto dst = rng.skipWhile([](int it){return it < 0 || it > 10;});

    auto vec = dst.toVector();

    CheckRangeEqArray(dst, ans);
}

TEST(SkipWhileRange, ManyToMany)
{
    int src[] = {1,2,3,4,5,6};
    int ans[] = {1,2,3,4,5,6};

    auto rng = from(src);
    auto dst = rng.skipWhile([](int it){return it < 0 && it > 6;});

    CheckRangeEqArray(dst, ans);
}

TEST(SkipWhileRange, ManyToLess)
{
    int src[] = {1,2,3,4,5,6};
    int ans[] = {3,4,5,6};

    auto rng = from(src);
    auto dst = rng.skipWhile([](int it){return it < 3 || it > 4;});

    CheckRangeEqArray(dst, ans);
}

TEST(SkipWhileRange, ManyToOne)
{
    int src[] = {1,2,3,4,5,6};
    int ans[] = {6};

    auto rng = from(src);
    auto dst = rng.skipWhile([](int it){return it != 6;});

    CheckRangeEqArray(dst, ans);
}

TEST(SkipWhileRange, ManyToZero)
{
    int src[] = {1,2,3,4,5,6};

    auto rng = from(src);
    auto dst = rng.skipWhile([](int it){return it > 0;});

    EXPECT_THROW(dst.nextObject(), EnumeratorEndException);
}

//////////////////////////////////////////////////////////////////////////

TEST(SkipWhileRange, OneToOne)
{
    int src[] = {5};
    int ans[] = {5};

    auto rng = from(src);
    auto dst = rng.skipWhile([](int it){return it != 5;});

    CheckRangeEqArray(dst, ans);
}

TEST(SkipWhileRange, OneToZero)
{
    int src[] = {5};

    auto rng = from(src);
    auto dst = rng.skipWhile([](int it){return it == 5;});

    EXPECT_THROW(dst.nextObject(), EnumeratorEndException);
}

TEST(SkipWhileRange, ZeroToZero)
{
    std::vector<int> src;

    auto rng = from(src);
    auto dst = rng.skipWhile([](int){return false;});

    EXPECT_THROW(rng.nextObject(), EnumeratorEndException);
}

//////////////////////////////////////////////////////////////////////////
