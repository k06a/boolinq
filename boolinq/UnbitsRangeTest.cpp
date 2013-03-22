#include <vector>
#include <string>

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "CommonTests.h"

#include "IterRange.h"
#include "UnbitsRange.h"

using namespace boolinq;

//////////////////////////////////////////////////////////////////////////

TEST(UnbitsRange, OneByteDefault)
{
    int src[] = {1,0,1,0,1,0,1,0};
    int ans[] = {0xAA};
    
    auto rng = range(src);
    auto dst = unbits(rng);

    CheckRangeEqArray(dst, ans);
}

TEST(UnbitsRange, OneByteHL)
{
    int src[] = {1,0,1,0,1,0,1,0};
    int ans[] = {0xAA};
    
    auto rng = range(src);
    auto dst = unbits<HighToLow>(rng);

    CheckRangeEqArray(dst, ans);
}

TEST(UnbitsRange, OneByteLH)
{
    int src[] = {0,1,0,1,0,1,0,1};
    int ans[] = {0xAA};
    
    auto rng = range(src);
    auto dst = unbits<LowToHigh>(rng);

    CheckRangeEqArray(dst, ans);
}