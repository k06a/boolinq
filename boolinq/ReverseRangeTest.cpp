#include <list>
#include <deque>
#include <vector>
#include <string>

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "CommonTests.h"

#include "IterRange.h"
#include "ReverseRange.h"

using namespace boolinq;

TEST(ReverseRange, IntVector)
{
    int src[] = {1,2,3,4};
    int ans[] = {4,3,2,1};

    auto rng = range(src);
    auto dst = reverse(rng);

    CheckRangeEqArray(dst, ans);
}

TEST(ReverseRange, DoubleReverse)
{
    int src[] = {1,2,3,4};
    int ans[] = {1,2,3,4};

    auto rng = range(src);
    auto dst = reverse(reverse(rng));

    CheckRangeEqArray(dst, ans);
}