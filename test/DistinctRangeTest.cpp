#include <vector>
#include <string>

#include <gtest/gtest.h>
#include "CommonTests.h"

#include "boolinq.h"

using namespace boolinq;

//////////////////////////////////////////////////////////////////////////

TEST(DistinctRange, Ints1to6)
{
    int src[] = {4,5,3,1,4,2,1,4,6};
    int ans[] = {1,2,3,4,5,6};
    
    auto rng = from(src);
    auto dst = rng.distinct();
    
    CheckRangeEqSet(dst, ans);
}

TEST(DistinctRange, IntMirrorFront)
{
    int src[]   = {3,2,1,0,1,2,3};
    int ans[]  = {0,1,2,3};
    
    auto rng = from(src);
    auto dst = rng.distinct();

    CheckRangeEqSet(dst, ans);
}

TEST(DistinctRange, ManyEqualsFront)
{
    int src[] = {1,1,1,1};
    int ans[] = {1};

    auto rng = from(src);
    auto dst = rng.distinct();
    
    CheckRangeEqSet(dst, ans);
}

TEST(DistinctRange, ManyEqualsWithOneFront)
{
    int src[] = {1,1,2,1};
    int ans[] = {1,2};

    auto rng = from(src);
    auto dst = rng.distinct();

    CheckRangeEqSet(dst, ans);
}

TEST(DistinctRange, OneFieldFront)
{
    struct Man
    {
        std::string name;
        int age;

        bool operator < (const Man & man) const
        {
            return (name < man.name)
                || (name == man.name && age < man.age);
        }

        bool operator == (const Man & man) const
        {
            return (name == man.name);
        }

        bool operator == (const std::string & name) const
        {
            return (this->name == name);
        }
    };

    Man src[] =
    {
        {"Anton",1},
        {"Taran",2},
        {"Poker",3},
        {"Agata",4},
        {"Mango",2},
        {"Banan",1},
    };

    std::string ans[] =
    {
        "Anton",
        "Taran",
        "Poker",
        "Agata",
    };

    auto rng = from(src);
    auto dst = rng.distinct([](const Man & man){return man.age;});

    CheckRangeEqSet(dst, ans);
}
