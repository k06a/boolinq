#pragma once

namespace boolinq
{
    // for_each(for_each(xxx, ...), ...)

    template<typename R, typename F>
    void for_each(R r, F f)
    {
        while (!r.empty())
            f(r.popFront());
    }

    // xxx.for_each(...).for_each(...)

    template<template<typename> class TLinq, typename R>
    class ForEach_mixin
    {
    public:
        template<typename F>
        void for_each(F f) const
        {
            return boolinq::for_each(((TLinq<R>*)this)->r,f);
        }
    };
}
// namespace boolinq
