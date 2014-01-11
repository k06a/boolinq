#include <list>
#include <deque>
#include <vector>
#include <string>

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "CommonTests.h"

#include "boolinq.h"

using namespace boolinq;

TEST(ReverseRange, IntVector)
{
    int src[] = {1,2,3,4};
    int ans[] = {4,3,2,1};

    auto rng = from(src);
    auto dst = rng.reverse();

    CheckRangeEqArray(dst, ans);
}

TEST(ReverseRange, DoubleReverse)
{
    int src[] = {1,2,3,4};
    int ans[] = {1,2,3,4};

    auto rng = from(src);
    auto dst = rng.reverse().reverse();

    CheckRangeEqArray(dst, ans);
}