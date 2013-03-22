#include <list>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "IterRange.h"
#include "ToList.h"

using namespace boolinq;

TEST(ToList, List2List)
{
    std::list<int> src;
    src.push_back(100);
    src.push_back(200);
    src.push_back(300);

    auto rng = range(src);
    auto dst = toList(rng);

    EXPECT_EQ(dst,src);
}
