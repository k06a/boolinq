#pragma once

//////////////////////////////////////////////////////////////////////////
// Compare Range with array
//////////////////////////////////////////////////////////////////////////

template<typename R, typename T, int N, typename F>
void CheckRangeEqArrayFront(R dst, T (&ans)[N], F f)
{
    for (int i = 0; i < N; i++)
    {
        EXPECT_FALSE(dst.empty());
        EXPECT_EQ(f(ans[i]),   f(dst.front()));
        EXPECT_EQ(f(ans[N-1]), f(dst.back()));
        EXPECT_EQ(f(ans[i]),   f(dst.popFront()));
    }

    EXPECT_TRUE(dst.empty());
}

template<typename R, typename T, int N, typename F>
void CheckRangeEqArrayBack(R dst, T (&ans)[N], F f)
{
    for (int i = N; i > 0; i--)
    {
        EXPECT_FALSE(dst.empty());
        EXPECT_EQ(f(ans[0]),   f(dst.front()));
        EXPECT_EQ(f(ans[i-1]), f(dst.back()));
        EXPECT_EQ(f(ans[i-1]), f(dst.popBack()));
    }

    EXPECT_TRUE(dst.empty());
}

template<typename R, typename T, int N, typename F>
void CheckRangeEqArrayTwisted(R dst, T (&ans)[N], F f, int bit)
{
    int b = 0;
    int e = N-1;

    for (int i = 0; i < N; i++)
    {
        EXPECT_FALSE(dst.empty());
        EXPECT_EQ(f(ans[b]), f(dst.front()));
        EXPECT_EQ(f(ans[e]), f(dst.back()));

        if (bit ^= 1)
            EXPECT_EQ(f(ans[b++]), f(dst.popFront()));
        else
            EXPECT_EQ(f(ans[e--]), f(dst.popBack()));
    }

    EXPECT_TRUE(dst.empty());
}

template<typename R, typename T, int N, typename F>
void CheckRangeEqArrayFrontBack(R dst, T (&ans)[N], F f)
{
    CheckRangeEqArrayTwisted(dst,ans,f,0);
}

template<typename R, typename T, int N, typename F>
void CheckRangeEqArrayBackFront(R dst, T (&ans)[N], F f)
{
    CheckRangeEqArrayTwisted(dst,ans,f,1);
}

template<typename R, typename T, int N, typename F>
void CheckRangeEqArray(R dst, T (&ans)[N], F f)
{
    CheckRangeEqArrayFront(dst,ans,f);
    CheckRangeEqArrayBack(dst,ans,f);
    CheckRangeEqArrayFrontBack(dst,ans,f);
    CheckRangeEqArrayBackFront(dst,ans,f);
}

//////////////////////////////////////////////////////////////////////////

template<typename R, typename T, int N>
void CheckRangeEqArrayFront(R dst, T (&ans)[N])
{
    CheckRangeEqArrayFront(dst, ans, [](const T & a)->T{return a;});
}

template<typename R, typename T, int N>
void CheckRangeEqArrayBack(R dst, T (&ans)[N])
{
    CheckRangeEqArrayBack(dst, ans, [](const T & a)->T{return a;});
}

template<typename R, typename T, int N>
void CheckRangeEqArrayFrontBack(R dst, T (&ans)[N])
{
    CheckRangeEqArrayFrontBack(dst, ans, [](const T & a)->T{return a;});
}

template<typename R, typename T, int N>
void CheckRangeEqArrayBackFront(R dst, T (&ans)[N])
{
    CheckRangeEqArrayBackFront(dst, ans, [](const T & a)->T{return a;});
}

template<typename R, typename T, int N>
void CheckRangeEqArray(R dst, T (&ans)[N])
{
    CheckRangeEqArray(dst, ans, [](const T & a)->T{return a;});
}

//////////////////////////////////////////////////////////////////////////
// Compare Range with set
//////////////////////////////////////////////////////////////////////////

template<typename T, int N>
std::set<T> ArrayToSet(T (&ans)[N])
{
    std::set<T> res;
    for(int i = 0; i < N; i++)
        res.insert(ans[i]);

    EXPECT_EQ(N, res.size());

    return res;
}

template<typename R, typename T, int N, typename F>
void CheckRangeEqSetFront(R r, T (&ans)[N], F f) 
{
    std::set<T> result;
    while (!r.empty())
        result.insert(f(r.popFront()));

    EXPECT_EQ(ArrayToSet(ans),result);
}

template<typename R, typename T, int N, typename F>
void CheckRangeEqSetBack(R r, T (&ans)[N], F f) 
{
    std::set<T> result;
    while (!r.empty())
        result.insert(f(r.popBack()));

    EXPECT_EQ(ArrayToSet(ans),result);
}

template<typename R, typename T, int N, typename F>
void CheckRangeEqSetTwisted(R r, F f, T (&ans)[N], int bit) 
{
    std::set<T> result;
    while (!r.empty())
    {
        if (bit ^= 1)
            result.insert(f(r.popFront()));
        else
            result.insert(f(r.popBack()));
    }

    EXPECT_EQ(ArrayToSet(ans),result);
}

template<typename R, typename T, int N, typename F>
void CheckRangeEqSetFrontBack(R r, T (&ans)[N], F f) 
{
    CheckRangeEqSetTwisted(r,f,ans,0);
}

template<typename R, typename T, int N, typename F>
void CheckRangeEqSetBackFront(R r, T (&ans)[N], F f) 
{
    CheckRangeEqSetTwisted(r,f,ans,1);
}

template<typename R, typename T, int N, typename F>
void CheckRangeEqSet(R r, T (&ans)[N], F f) 
{
    CheckRangeEqSetFront(r,ans,f);
    CheckRangeEqSetBack(r,ans,f);
    CheckRangeEqSetFrontBack(r,ans,f);
    CheckRangeEqSetBackFront(r,ans,f);
}

//////////////////////////////////////////////////////////////////////////

template<typename R, typename T, int N>
void CheckRangeEqSetFront(R r, T (&ans)[N]) 
{
    CheckRangeEqSetFront(r, ans, [](const T & a)->T{return a;});
}

template<typename R, typename T, int N>
void CheckRangeEqSetBack(R r, T (&ans)[N]) 
{
    CheckRangeEqSetBack(r, ans, [](const T & a)->T{return a;});
}

template<typename R, typename T, int N>
void CheckRangeEqSetFrontBack(R r, T (&ans)[N]) 
{
    CheckRangeEqSetFrontBack(r, ans, [](const T & a)->T{return a;});
}

template<typename R, typename T, int N>
void CheckRangeEqSetBackFront(R r, T (&ans)[N]) 
{
    CheckRangeEqSetBackFront(r, ans, [](const T & a)->T{return a;});
}

template<typename R, typename T, int N>
void CheckRangeEqSet(R r, T (&ans)[N])
{
    CheckRangeEqSet(r, ans, [](const T & a)->T{return a;});
}