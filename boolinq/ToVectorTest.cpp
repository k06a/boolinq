#include <vector>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "IterRange.h"
#include "ToVector.h"

using namespace boolinq;

TEST(ToVector, Vector2Vector)
{
    std::vector<int> src;
    src.push_back(100);
    src.push_back(200);
    src.push_back(300);

    auto rng = range(src);
    auto dst = toVector(rng);

    EXPECT_EQ(dst,src);
}
