#pragma once

namespace boolinq
{
    // min(xxx, int)

    template<typename R, typename F>
    typename R::value_type min(R r, F f)
    {
        R min = r;
        while (!r.empty())
        {
            if (f(r.front()) < f(min.front()))
                min = r;
            r.popFront();
        }
        return min.front();
    }

    template<typename R>
    typename R::value_type min(R r)
    {
        typedef typename R::value_type value_type;
        return min(r,[](const value_type & a)->value_type{return a;});
    }

    // xxx.min(int)

    template<template<typename> class TLinq, typename R>
    class Min_mixin
    {
    public:
        typename R::value_type min() const
        {
            return boolinq::min(((TLinq<R>*)this)->r);
        }

        template<typename F>
        typename R::value_type min(F f) const
        {
            return boolinq::min(((TLinq<R>*)this)->r,f);
        }
    };
}
// namespace boolinq
