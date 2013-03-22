#pragma once

namespace boolinq
{
    // avg(xxx) and avg(xxx,lambda)

    template<typename R, typename F>
    auto avg(R r, F f) -> decltype(f(r.front()) + f(r.back()))
    {
        typedef decltype(f(r.front()) + f(r.back())) value_type;
        value_type val = value_type();
        int count = 0;
        for (; !r.empty(); r.popFront())
        {
            val = val + f(r.front());
            count++;
        }
        return val/count;
    }

    template<typename R>
    auto avg(R r) -> decltype(r.front() + r.back())
    {
        typedef decltype(r.front() + r.back()) value_type;
        return avg(r,[](const value_type & a)->value_type{return a;});
    }

    // xxx.avg() and xxx.avg(lambda)

    template<template<typename> class TLinq, typename R>
    class Avg_mixin
    {
        template<typename F, typename TArg>
        static auto get_return_type(F * f = NULL, TArg * arg = NULL)
            -> decltype((*f)(*arg));          

    public:
        //TODO: Invalid return type ... should be (value_type + value_type)
        typename R::value_type avg() const
        {
            return boolinq::avg(((TLinq<R>*)this)->r);
        }

        template<typename F>
        auto avg(F f) const -> decltype(get_return_type<F,typename R::value_type>()
                                        + get_return_type<F,typename R::value_type>())
        {
            return boolinq::avg(((TLinq<R>*)this)->r,f);
        }
    };
}
// namespace boolinq
