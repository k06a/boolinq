#include <vector>
#include <string>

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "CommonTests.h"

#include "IterRange.h"
#include "WhereRange.h"

using namespace boolinq;

//////////////////////////////////////////////////////////////////////////

TEST(WhereRange, IntOdd)
{
    int src[] = {1,2,3,4,5,6};
    int ans[] = {1,  3,  5};

    auto rng = range(src);
    auto dst = where(rng, [](int a){return a%2 == 1;});
    
    CheckRangeEqArray(dst, ans);
}

//////////////////////////////////////////////////////////////////////////

TEST(WhereRange, FirstLetterFront)
{
    std::string src[] =
    {
        "apple",
        "blackberry",
        "adobe",
        "microsoft",
        "nokia",
    };

    std::string ans[] =
    {
        "apple",
        "adobe",
    };

    auto rng = range(src);
    auto dst = where(rng, [](std::string a){return a[0] == 'a';});
    
    CheckRangeEqArray(dst, ans);
}

//////////////////////////////////////////////////////////////////////////

TEST(WhereRange, NameAgeLess)
{
    struct NameAge
    {
        std::string name;
        int age;
    };

    NameAge src[] =
    {
        {"man1",20},
        {"man2",15},
        {"man3",30},
        {"man4",14},
        {"man5",18},
    };

    NameAge ans[] =
    {
        {"man2",20},
        {"man4",15},
    };

    auto rng = range(src);
    auto dst = where(rng, [](const NameAge & a){return a.age < 18;});
    
    CheckRangeEqArray(dst, ans, [](const NameAge & a){return a.name;});
}

//////////////////////////////////////////////////////////////////////////

TEST(WhereRange, MayToOne)
{
    int src[] = {0,1,2};
    int ans[] = {1};
    
    auto rng = range(src);
    auto dst = where(rng, [](int a){return a == 1;});

    CheckRangeEqArray(dst, ans);
}

TEST(WhereRange, OneToOne)
{
    int src[] = {5};
    int ans[] = {5};

    auto rng = range(src);
    auto dst = where(rng, [](int a){return a>0;});

    CheckRangeEqArray(dst, ans);
}

TEST(WhereRange, ManyToZero)
{
    int src[] = {0,1,2};
    
    auto rng = range(src);
    auto dst = where(rng, [](int a){return a == 5;});

    EXPECT_TRUE(dst.empty());
}

TEST(WhereRange, OneToZero)
{
    int src[] = {5};
    
    auto rng = range(src);
    auto dst = where(rng, [](int a){return a>10;});

    EXPECT_TRUE(dst.empty());
}

TEST(WhereRange, ZeroToZero)
{
    std::vector<int> src;

    auto rng = range(src);
    auto dst = where(rng, [](int a){return a>0;});

    EXPECT_TRUE(rng.empty());
}
