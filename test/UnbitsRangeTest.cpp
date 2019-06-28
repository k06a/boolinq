#include <vector>
#include <string>

#include <gtest/gtest.h>
#include "CommonTests.h"

#include "boolinq.h"

using namespace boolinq;

//////////////////////////////////////////////////////////////////////////

TEST(UnbitsRange, OneByteDefault)
{
    int src[] = {1,0,1,0,1,0,1,0};
    int ans[] = {0xAA};
    
    auto rng = from(src);
    auto dst = rng.unbits();

    CheckRangeEqArray(dst, ans);
}

TEST(UnbitsRange, OneByteHL)
{
    int src[] = {1,0,1,0,1,0,1,0};
    int ans[] = {0xAA};
    
    auto rng = from(src);
    auto dst = rng.unbits(BitsHighToLow);

    CheckRangeEqArray(dst, ans);
}

TEST(UnbitsRange, OneByteLH)
{
    int src[] = {0,1,0,1,0,1,0,1};
    int ans[] = {0xAA};
    
    auto rng = from(src);
    auto dst = rng.unbits(BitsLowToHigh);

    CheckRangeEqArray(dst, ans);
}
