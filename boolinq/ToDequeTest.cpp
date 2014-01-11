#include <deque>

#include <gtest/gtest.h>

#include "boolinq.h"

using namespace boolinq;

TEST(ToDeque, Deque2Deque)
{
    std::deque<int> src;
    src.push_back(100);
    src.push_back(200);
    src.push_back(300);

    auto rng = from(src);
    auto dst = rng.toDeque();

    EXPECT_EQ(dst,src);
}
