#include <vector>
#include <string>

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "CommonTests.h"

#include "IterRange.h"
#include "UnbytesRange.h"

using namespace boolinq;

//////////////////////////////////////////////////////////////////////////

TEST(UnbytesRange, OneIntDefault)
{
    unsigned char src[] = {0xAA,0xBB,0xCC,0xDD};
    int ans[] = {0xDDCCBBAA};

    auto rng = range(src);
    auto dst = unbytes<int>(rng);

    CheckRangeEqArray(dst, ans);
}

TEST(UnbytesRange, OneIntFL)
{
    unsigned char src[] = {0xAA,0xBB,0xCC,0xDD};
    int ans[] = {0xDDCCBBAA};

    auto rng = range(src);
    auto dst = unbytes<int,FirstToLast>(rng);

    CheckRangeEqArray(dst, ans);
}

TEST(UnbytesRange, OneIntLF)
{
    unsigned char src[] = {0xAA,0xBB,0xCC,0xDD};
    int ans[] = {0xAABBCCDD};

    auto rng = range(src);
    auto dst = unbytes<int,LastToFirst>(rng);

    CheckRangeEqArray(dst, ans);
}

//////////////////////////////////////////////////////////////////////////

TEST(UnbytesRange, TwoIntsDefault)
{
    unsigned char src[] = 
    {
        0x78,0x56,0x34,0x12,
        0xAA,0xBB,0xCC,0xDD,
    };
    int ans[] = {0x12345678,0xDDCCBBAA};

    auto rng = range(src);
    auto dst = unbytes<int>(rng);

    CheckRangeEqArray(dst, ans);
}

TEST(UnbytesRange, TwoIntsFL)
{
    unsigned char src[] = 
    {
        0x78,0x56,0x34,0x12,
        0xAA,0xBB,0xCC,0xDD,
    };
    int ans[] = {0x12345678,0xDDCCBBAA};

    auto rng = range(src);
    auto dst = unbytes<int,FirstToLast>(rng);

    CheckRangeEqArray(dst, ans);
}

TEST(UnbytesRange, TwoIntsLF)
{
    unsigned char src[] = 
    {
        0x78,0x56,0x34,0x12,
        0xAA,0xBB,0xCC,0xDD,
    };
    int ans[] = {0x78563412,0xAABBCCDD};

    auto rng = range(src);
    auto dst = unbytes<int,LastToFirst>(rng);

    CheckRangeEqArray(dst, ans);
}

//////////////////////////////////////////////////////////////////////////

TEST(UnbytesRange, EmptyDefault)
{
    std::vector<unsigned char> src;
    
    auto rng = range(src);
    auto dst = unbytes<int>(rng);

    EXPECT_TRUE(dst.empty());
}
