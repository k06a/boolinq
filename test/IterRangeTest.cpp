#include <list>
#include <deque>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <array>

#include <gtest/gtest.h>
#include "CommonTests.h"

#include "boolinq.h"

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

    CheckRangeEqArray(from(lst), ans);
    CheckRangeEqArray(from<int>(lst.begin(), lst.end()), ans);
    CheckRangeEqArray(from<int>(lst.cbegin(), lst.cend()), ans);
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

    CheckRangeEqArray(from(dck), ans);
    CheckRangeEqArray(from<int>(dck.begin(), dck.end()), ans);
    CheckRangeEqArray(from<int>(dck.cbegin(), dck.cend()), ans);
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

    CheckRangeEqArray(from(vec), ans);
    CheckRangeEqArray(from<int>(vec.begin(), vec.end()), ans);
    CheckRangeEqArray(from<int>(vec.cbegin(), vec.cend()), ans);
}

TEST(IterRange, SetInt)
{
    std::set<int> set = {1,2,3,4,5};
    int ans[] = {1,2,3,4,5};

    CheckRangeEqSet(from(set), ans);
    CheckRangeEqSet(from<int>(set.begin(), set.end()), ans);
    CheckRangeEqSet(from<int>(set.cbegin(), set.cend()), ans);
}

TEST(IterRange, MapInt)
{
    std::map<int, int> map = {{5,1},{4,2},{3,3},{2,4},{1,5}};
    std::pair<int, int> ans[] = {{5,1},{4,2},{3,3},{2,4},{1,5}};

    CheckRangeEqArray(from(map)
        .orderBy([](std::pair<int,int> p){ return p.second; }), ans);
    CheckRangeEqArray(from<std::pair<int,int> >(map.begin(), map.end())
        .orderBy([](std::pair<int,int> p){ return p.second; }), ans);
    CheckRangeEqArray(from<std::pair<int,int> >(map.cbegin(), map.cend())
        .orderBy([](std::pair<int,int> p){ return p.second; }), ans);
}

TEST(IterRange, StdArrayInt)
{
    std::array<int, 5> arr = {1,2,3,4,5};
    int ans[] = {1,2,3,4,5};

    CheckRangeEqArray(from(arr), ans);
    CheckRangeEqArray(from<int>(arr.begin(), arr.end()), ans);
    CheckRangeEqArray(from<int>(arr.cbegin(), arr.cend()), ans);
}

TEST(IterRange, ArrayInt)
{
    int arr[] = {1,2,3,4,5};
    int * ptr = (int*)arr;
    
    int ans[] = {1,2,3,4,5};

    CheckRangeEqArray(from(arr), ans);
    CheckRangeEqArray(from<int>(ptr, 5), ans);
    CheckRangeEqArray(from<int>(ptr, ptr+5), ans);
}

//////////////////////////////////////////////////////////////////////////

TEST(IterRange, OneElement)
{
    int src[] = {5};
    int ans[] = {5};

    auto rng = from(src);

    CheckRangeEqArray(rng, ans);
}

TEST(IterRange, EmptyVector)
{
    std::vector<int> src;
    
    auto rng = from(src);

    EXPECT_THROW(rng.nextObject(), EnumeratorEndException);
}
