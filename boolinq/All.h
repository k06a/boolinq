#pragma once

namespace boolinq
{
    // all(xxx) and all(xxx,lambda)

    template<typename R, typename F>
    bool all(R r, F f)
    {
        while (!r.empty())
            if (!f(r.popFront()))
                return false;
        return true;
    }

    template<typename R>
    bool all(R r)
    {
        typedef typename R::value_type value_type;
        return all(r,[](const value_type & a)->value_type{return a;});
    }

    // xxx.all() and xxx.all(lambda)

    template<template<typename> class TLinq, typename R>
    class All_mixin
    {
    public:
        bool all() const
        {
            return boolinq::all(((TLinq<R>*)this)->r);
        }

        template<typename F>
        bool all(F f) const
        {
            return boolinq::all(((TLinq<R>*)this)->r,f);
        }
    };
}
// namespace boolinq
