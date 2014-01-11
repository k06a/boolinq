#include <vector>

#include <gtest/gtest.h>

#include "boolinq.h"

using namespace boolinq;

TEST(ToVector, Vector2Vector)
{
    std::vector<int> src;
    src.push_back(100);
    src.push_back(200);
    src.push_back(300);

    auto rng = from(src);
    auto dst = rng.toVector();

    EXPECT_EQ(dst,src);
}
