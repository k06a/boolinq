#include <vector>
#include <string>

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "CommonTests.h"

#include "IterRange.h"
#include "OrderByRange.h"

using namespace boolinq;

//////////////////////////////////////////////////////////////////////////

TEST(OrderByRange, RandomIntsWithDuplicates)
{
    int src[] = {4,5,3,1,4,2,1,4,6};
    int ans[] = {1,1,2,3,4,4,4,5,6};

    auto rng = range(src);
    auto dst = orderBy(rng);

    CheckRangeEqArray(dst, ans);
}

TEST(OrderByRange, ReverseInts)
{
    int src[] = {4,3,2,1};
    int ans[] = {1,2,3,4};

    auto rng = range(src);
    auto dst = orderBy(rng);

    CheckRangeEqArray(dst, ans);
}

TEST(OrderByRange, ThreeElements)
{
    int src[] = {1,3,2};
    int ans[] = {1,2,3};

    auto rng = range(src);
    auto dst = orderBy(rng);

    CheckRangeEqArray(dst, ans);
}

//////////////////////////////////////////////////////////////////////////

TEST(OrderByRange, OneElement)
{
    int src[] = {5};
    int ans[] = {5};
    
    auto rng = range(src);
    auto dst = orderBy(rng);

    CheckRangeEqArray(dst, ans);
}

TEST(OrderByRange, NoElements)
{
    std::vector<int> src;
    
    auto rng = range(src);
    auto dst = orderBy(rng);

    EXPECT_TRUE(dst.empty());
}

//////////////////////////////////////////////////////////////////////////

TEST(OrderByRange, RandomStringByContent)
{
    std::string src[] =
    {
        "microsoft",
        "intel",
        "nokia",
        "apple",
        "oracle",
        "sun",
    };

    std::string ans[] =
    {
        "apple",
        "intel",
        "microsoft",
        "nokia",
        "oracle",
        "sun",
    };

    auto rng = range(src);
    auto dst = orderBy(rng);

    CheckRangeEqArray(dst, ans);
}

TEST(OrderByRange, RandomStringByLength)
{
    std::string src[] =
    {
        "microsoft",
        "intel",
        "nokia",
        "apple",
        "oracle",
        "sun",
    };

    std::string ans[] =
    {
        "sun",
        "intel",
        "nokia",
        "apple",
        "oracle",
        "microsoft",
    };

    auto rng = range(src);
    auto dst = orderBy(rng, [](std::string a){return a.size();});

    CheckRangeEqArray(dst, ans, [](const std::string & s){return s.size();});
}