#include <vector>
#include <string>

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "CommonTests.h"

#include "IterRange.h"
#include "SelectRange.h"

using namespace boolinq;

TEST(SelectRange, Mul2)
{
    int src[] = {1,2,3,4};
    int ans[] = {2,4,6,8};

    auto rng = range(src);
    auto dst = select(rng, [](int a){return a * 2;});

    CheckRangeEqArray(dst, ans);
}

TEST(SelectRange, MakeChar)
{
    int src[] = {1,2,3,4};
    char ans[] = {'1','2','3','4'};

    auto rng = range(src);
    auto dst = select(rng, [](int a){return (char)(a+'0');});

    CheckRangeEqArray(dst, ans);
}

TEST(SelectRange, MakeString)
{
    int src[] = {1,2,3,4};

    static std::string ans[] =
    {
        "hello",
        "world",
        "apple",
        "intel",
    };

    auto rng = range(src);
    auto dst = select(rng, [](int a){return ans[a-1];});

    CheckRangeEqArray(dst, ans);
}
