#include <vector>
#include <string>

#include <gtest/gtest.h>
#include "CommonTests.h"

#include "boolinq.h"

using namespace boolinq;

//////////////////////////////////////////////////////////////////////////

TEST(OrderByRange, RandomIntsWithDuplicates)
{
    int src[] = {4,5,3,1,4,2,1,4,6};
    int ans[] = {1,1,2,3,4,4,4,5,6};

    auto rng = from(src);
    auto dst = rng.orderBy();

    CheckRangeEqArray(dst, ans);
}

TEST(OrderByRange, ReverseInts)
{
    int src[] = {4,3,2,1};
    int ans[] = {1,2,3,4};

    auto rng = from(src);
    auto dst = rng.orderBy();

    CheckRangeEqArray(dst, ans);
}

TEST(OrderByRange, ThreeElements)
{
    int src[] = {1,3,2};
    int ans[] = {1,2,3};

    auto rng = from(src);
    auto dst = rng.orderBy();

    CheckRangeEqArray(dst, ans);
}

//////////////////////////////////////////////////////////////////////////

TEST(OrderByRange, OneElement)
{
    int src[] = {5};
    int ans[] = {5};
    
    auto rng = from(src);
    auto dst = rng.orderBy();

    CheckRangeEqArray(dst, ans);
}

TEST(OrderByRange, NoElements)
{
    std::vector<int> src;
    
    auto rng = from(src);
    auto dst = rng.orderBy();

    EXPECT_THROW(dst.nextObject(), LinqEndException);
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

    auto rng = from(src);
    auto dst = rng.orderBy();

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

    auto rng = from(src);
    auto dst = rng.orderBy([](std::string a){return a.size();});

    CheckRangeEqArray(dst, ans, [](const std::string & s){return s.size();});
}
