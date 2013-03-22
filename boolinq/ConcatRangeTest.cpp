#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "CommonTests.h"

#include "IterRange.h"
#include "ConcatRange.h"

using namespace boolinq;

TEST(ConcatRange, ArrayArray)
{
    int src1[] = {1,2,3,4,5};
    int src2[] = {6,7,8,9};

    int ans[] = {1,2,3,4,5,6,7,8,9};

    auto rng1 = range(src1);
    auto rng2 = range(src2);
    auto dst = unionAll(rng1,rng2);
             
    CheckRangeEqArray(dst, ans);
}

TEST(ConcatRange, ArrayVector)
{
    int src1[] = {1,2,3,4,5};
    std::vector<int> src2;
    src2.push_back(6);
    src2.push_back(7);
    src2.push_back(8);
    src2.push_back(9);

    int ans[] = {1,2,3,4,5,6,7,8,9};

    auto rng1 = range(src1);
    auto rng2 = range(src2);
    auto dst = unionAll(rng1,rng2);

    CheckRangeEqArray(dst, ans);
}

TEST(ConcatRange, ArrayVectorArray)
{
    int src1[] = {1,2,3,4,5};
    std::vector<int> src2;
    src2.push_back(6);
    src2.push_back(7);
    src2.push_back(8);
    src2.push_back(9);
    int src3[] = {10,11,12,13,14,15};

    int ans[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};

    auto rng1 = range(src1);
    auto rng2 = range(src2);
    auto rng3 = range(src3);
    auto dst = unionAll(unionAll(rng1,rng2),rng3);

    CheckRangeEqArray(dst, ans);
}