#pragma once

namespace boolinq
{
    // max(xxx, int)

    template<typename R, typename F>
    typename R::value_type max(R r, F f)
    {
        R max = r;
        while (!r.empty())
        {
            if (f(r.front()) > f(max.front()))
                max = r;
            r.popFront();
        }
        return max.front();
    }

    template<typename R>
    typename R::value_type max(R r)
    {
        typedef typename R::value_type value_type;
        return max(r,[](const value_type & a)->value_type{return a;});
    }

    // xxx.max(int)

    template<template<typename> class TLinq, typename R>
    class Max_mixin
    {
    public:
        typename R::value_type max() const
        {
            return boolinq::max(((TLinq<R>*)this)->r);
        }

        template<typename F>
        typename R::value_type max(F f) const
        {
            return boolinq::max(((TLinq<R>*)this)->r,f);
        }
    };
}
// namespace boolinq
