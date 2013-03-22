#pragma once

namespace boolinq
{
    // sum(xxx) and sum(xxx,lambda)

    template<typename R, typename F>
    auto sum(R r, F f) -> decltype(f(r.front()) + f(r.back()))
    {
        typedef decltype(f(r.front()) + f(r.back())) value_type;
        value_type val = value_type();
        for (; !r.empty(); r.popFront())
            val = val + f(r.front());
        return val;
    }

    template<typename R>
    auto sum(R r) -> decltype(r.front() + r.back())
    {
        typedef decltype(r.front() + r.back()) value_type;
        return sum(r,[](const value_type & a)->value_type{return a;});
    }

    // xxx.sum() and xxx.sum(lambda)

    template<template<typename> class TLinq, typename R>
    class Sum_mixin
    {
        template<typename F, typename TArg>
        static auto get_return_type(F * f = NULL, TArg * arg = NULL)
                    -> decltype((*f)(*arg));          

    public:
        //TODO: Invalid return type ... should be (value_type + value_type)
        typename R::value_type sum() const
        {
            return boolinq::sum(((TLinq<R>*)this)->r);
        }

        template<typename F>
        auto sum(F f) const -> decltype(get_return_type<F,typename R::value_type>()
                                        + get_return_type<F,typename R::value_type>())
        {
            return boolinq::sum(((TLinq<R>*)this)->r,f);
        }
    };
}
// namespace boolinq
