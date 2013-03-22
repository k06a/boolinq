#include <list>
#include <deque>
#include <vector>
#include <string>

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "CommonTests.h"

#include "IterRange.h"

using namespace boolinq;

//////////////////////////////////////////////////////////////////////////

TEST(IterRange, ListInt)
{
    std::list<int> lst;
    lst.push_back(1);
    lst.push_back(2);
    lst.push_back(3);
    lst.push_back(4);
    lst.push_back(5);

    int ans[] = {1,2,3,4,5};

    CheckRangeEqArray(range(lst), ans);
    CheckRangeEqArray(range(lst.begin(), lst.end()), ans);
    CheckRangeEqArray(range(lst.cbegin(), lst.cend()), ans);
}

TEST(IterRange, DequeInt)
{
    std::deque<int> dck;
    dck.push_back(1);
    dck.push_back(2);
    dck.push_back(3);
    dck.push_back(4);
    dck.push_back(5);
    
    int ans[] = {1,2,3,4,5};

    CheckRangeEqArray(range(dck), ans);
    CheckRangeEqArray(range(dck.begin(), dck.end()), ans);
    CheckRangeEqArray(range(dck.cbegin(), dck.cend()), ans);
}

TEST(IterRange, VectorInt)
{
    std::vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(5);
    
    int ans[] = {1,2,3,4,5};

    CheckRangeEqArray(range(vec), ans);
    CheckRangeEqArray(range(vec.begin(), vec.end()), ans);
    CheckRangeEqArray(range(vec.cbegin(), vec.cend()), ans);
}

TEST(IterRange, ArrayInt)
{
    int arr[] = {1,2,3,4,5};
    int * ptr = (int*)arr;
    
    int ans[] = {1,2,3,4,5};

    CheckRangeEqArray(range(arr), ans);
    CheckRangeEqArray(range(ptr, 5), ans);
    CheckRangeEqArray(range(ptr, ptr+5), ans);
}

//////////////////////////////////////////////////////////////////////////

TEST(IterRange, OneElement)
{
    int src[] = {5};
    int ans[] = {5};

    auto rng = range(src);

    CheckRangeEqArray(rng, ans);
}

TEST(IterRange, EmptyVector)
{
    std::vector<int> src;
    
    auto rng = range(src);

    EXPECT_TRUE(rng.empty());
}