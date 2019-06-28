#include <vector>
#include <string>

#include <gtest/gtest.h>
#include "CommonTests.h"

#include "boolinq.h"

using namespace boolinq;

//////////////////////////////////////////////////////////////////////////

TEST(TakeRange, ManyToMore)
{
    int src[] = {1,2,3,4,5,6};
    int ans[] = {1,2,3,4,5,6};

    auto rng = from(src);
    auto dst = rng.take(10);

    CheckRangeEqArray(dst, ans);
}

TEST(TakeRange, ManyToMany)
{
    int src[] = {1,2,3,4,5,6};
    int ans[] = {1,2,3,4,5,6};

    auto rng = from(src);
    auto dst = rng.take(6);

    CheckRangeEqArray(dst, ans);
}

TEST(TakeRange, ManyToLess)
{
    int src[] = {1,2,3,4,5,6};
    int ans[] = {1,2,3};

    auto rng = from(src);
    auto dst = rng.take(3);

    CheckRangeEqArray(dst, ans);
}

TEST(TakeRange, ManyToOne)
{
    int src[] = {1,2,3,4,5,6};
    int ans[] = {1};

    auto rng = from(src);
    auto dst = rng.take(1);

    CheckRangeEqArray(dst, ans);
}

TEST(TakeRange, ManyToZero)
{
    int src[] = {1,2,3,4,5,6};

    auto rng = from(src);
    auto dst = rng.take(0);

    EXPECT_THROW(dst.next(), LinqEndException);
}

//////////////////////////////////////////////////////////////////////////

TEST(TakeRange, OneToMore)
{
    int src[] = {5};
    int ans[] = {5};

    auto rng = from(src);
    auto dst = rng.take(5);

    CheckRangeEqArray(dst, ans);
}

TEST(TakeRange, OneToOne)
{
    int src[] = {5};
    int ans[] = {5};

    auto rng = from(src);
    auto dst = rng.take(1);

    CheckRangeEqArray(dst, ans);
}

TEST(TakeRange, OneToZero)
{
    int src[] = {5};

    auto rng = from(src);
    auto dst = rng.take(0);

    EXPECT_THROW(dst.next(), LinqEndException);
}

TEST(TakeRange, ZeroToZero)
{
    std::vector<int> src;

    auto rng = from(src);
    auto dst = rng.take(0);

    EXPECT_THROW(rng.next(), LinqEndException);
}

//////////////////////////////////////////////////////////////////////////
