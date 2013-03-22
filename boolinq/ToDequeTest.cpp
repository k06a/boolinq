#include <deque>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "IterRange.h"
#include "ToDeque.h"

using namespace boolinq;

TEST(ToDeque, Deque2Deque)
{
    std::deque<int> src;
    src.push_back(100);
    src.push_back(200);
    src.push_back(300);

    auto rng = range(src);
    auto dst = toDeque(rng);

    EXPECT_EQ(dst,src);
}
