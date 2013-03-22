#include <gmock/gmock.h>
#include <gtest/gtest.h>

////////////////////////////////////////////////////////////////

/*
template<class R, class T>
R find(R r, T value)
{
    for (; !r.empty(); r.popFront())
        if (value == r.front()) break;
    return r;
}

template<class R, class T>
R find_end(R r, T value)
{
    return retro(find(retro(r), value));
}
*/

////////////////////////////////////////////////////////////////

int main(int argc, char * argv[])
{
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}