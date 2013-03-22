#pragma once

namespace boolinq
{
    // any(xxx) and any(xxx,lambda)

    template<typename R, typename F>
    bool any(R r, F f)
    {
        while (!r.empty())
            if (f(r.popFront()))
                return true;
        return false;
    }

    template<typename R>
    bool any(R r)
    {
        typedef typename R::value_type value_type;
        return any(r,[](const value_type & a)->value_type{return a;});
    }

    // xxx.any() and xxx.any(lambda)

    template<template<typename> class TLinq, typename R>
    class Any_mixin
    {
    public:
        bool any() const
        {
            return boolinq::any(((TLinq<R>*)this)->r);
        }

        template<typename F>
        bool any(F f) const
        {
            return boolinq::any(((TLinq<R>*)this)->r,f);
        }
    };
}
// namespace boolinq
