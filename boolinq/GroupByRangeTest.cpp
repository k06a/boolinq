#include <vector>
#include <string>

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "CommonTests.h"

#include "boolinq.h"

using namespace boolinq;

//////////////////////////////////////////////////////////////////////////

/*

TEST(GroupByRange, IntsFront)
{
    int arr[] = {0,1,2,3,4,5,6,7,8,9};

    int ans_1[] = {1,4,7};
    int ans_2[] = {2,5,8};
    int ans_0[] = {0,3,6,9};

    auto rng = from(arr);
    auto dst = rng.groupBy([](int a){return a % 3;});

    EXPECT_EQ(1, dst.front().key());
    EXPECT_EQ(0, dst.back().key());
    CheckRangeEqArray(dst.front(), ans_1);
    CheckRangeEqArray(dst.back(), ans_0);
    CheckRangeEqArray(dst.popFront(), ans_1);
    
    EXPECT_EQ(2, dst.front().key());
    EXPECT_EQ(0, dst.back().key());
    CheckRangeEqArray(dst.front(), ans_2);
    CheckRangeEqArray(dst.back(), ans_0);
    CheckRangeEqArray(dst.popFront(), ans_2);

    EXPECT_EQ(0, dst.front().key());
    EXPECT_EQ(0, dst.back().key());
    CheckRangeEqArray(dst.front(), ans_0);
    CheckRangeEqArray(dst.back(), ans_0);
    CheckRangeEqArray(dst.popFront(), ans_0);

    EXPECT_THROW(dst.nextObject(), EnumeratorEndException);
}

TEST(GroupByRange, IntsBack)
{
    int arr[] = {0,1,2,3,4,5,6,7,8,9};

    int ans_1[] = {1,4,7};
    int ans_2[] = {2,5,8};
    int ans_0[] = {0,3,6,9};

    auto rng = from(arr);
    auto dst = groupBy(rng, [](int a){return a % 3;});

    EXPECT_EQ(1, dst.front().key());
    EXPECT_EQ(0, dst.back().key());
    CheckRangeEqArray(dst.front(), ans_1);
    CheckRangeEqArray(dst.back(), ans_0);
    CheckRangeEqArray(dst.popBack(), ans_0);

    EXPECT_EQ(1, dst.front().key());
    EXPECT_EQ(2, dst.back().key());
    CheckRangeEqArray(dst.front(), ans_1);
    CheckRangeEqArray(dst.back(), ans_2);
    CheckRangeEqArray(dst.popBack(), ans_2);

    EXPECT_EQ(1, dst.front().key());
    EXPECT_EQ(1, dst.back().key());
    CheckRangeEqArray(dst.front(), ans_1);
    CheckRangeEqArray(dst.back(), ans_1);
    CheckRangeEqArray(dst.popBack(), ans_1);

    EXPECT_THROW(dst.nextObject(), EnumeratorEndException);
}

//////////////////////////////////////////////////////////////////////////

TEST(GroupByRange, CountChildrenByAge)
{
    struct Child
    {
        std::string name;
        int age;

        bool operator == (const Child & rhs) const
        {
            return (name == rhs.name) && (age == rhs.age);
        }
    };  

    Child children[] =
    {
        {"Piter", 12},
        {"Bella", 14},
        {"Torry", 15},
        {"Holly", 12},
        {"Zamza", 13},
    };

    Child ans_false[] =
    {
        {"Bella", 14},
        {"Torry", 15},
    };

    Child ans_true[] =
    {
        {"Piter", 12},
        {"Holly", 12},
        {"Zamza", 13},
    };

    auto rng = from(children);
    auto dst = groupBy(rng, [](const Child & a){return a.age < 14;});

    EXPECT_EQ(false, dst.front().key());
    CheckRangeEqArray(dst.front(), ans_false);
    CheckRangeEqArray(dst.back(), ans_true);
    CheckRangeEqArray(dst.popFront(), ans_false);

    EXPECT_EQ(true, dst.front().key());
    CheckRangeEqArray(dst.front(), ans_true);
    CheckRangeEqArray(dst.back(), ans_true);
    CheckRangeEqArray(dst.popFront(), ans_true);

    EXPECT_THROW(dst.nextObject(), EnumeratorEndException);
}

*/