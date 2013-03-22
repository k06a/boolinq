#pragma once

namespace boolinq
{
    // count(xxx) and count(xxx,lambda)

    template<typename R>
    int count(R r)
    {
        int index = 0;
        for (; !r.empty(); r.popFront())
            index++;
        return index;
    }

    template<typename R, typename T>
    int count(R r, T t)
    {
        int index = 0;
        for (; !r.empty(); r.popFront())
            if (r.front() == t)
                index++;
        return index;
    }

    // xxx.count() and xxx.count(lambda)

    template<template<typename> class TLinq, typename R>
    class Count_mixin
    {
    public:
        int count() const
        {
            return boolinq::count(((TLinq<R>*)this)->r);
        }

        template<typename T>
        int count(T t) const
        {
            return boolinq::count(((TLinq<R>*)this)->r,t);
        }
    };
}
// namespace boolinq
