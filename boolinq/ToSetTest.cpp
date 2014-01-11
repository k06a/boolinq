#include <vector>

#include <gtest/gtest.h>

#include "boolinq.h"

using namespace boolinq;

TEST(ToSet, Vector2Set)
{
    std::vector<int> src;
    src.push_back(1);
    src.push_back(1);
    src.push_back(2);
    src.push_back(3);
    src.push_back(2);

    auto rng = from(src);
    auto dst = rng.toSet();

    EXPECT_EQ(3, dst.size());
    EXPECT_NE(dst.end(), dst.find(1));
    EXPECT_NE(dst.end(), dst.find(2));
    EXPECT_NE(dst.end(), dst.find(3));
}
