#pragma once

#include <allocators>

namespace boolinq
{
    // toContainer<std::vector>(xxx)
    // toContainer<QList>(xxx)
    
    template<template<typename> class X, typename R>
    X<typename R::value_type> toContainer(R r)
    {
        X<typename R::value_type> result;
        for (; !r.empty(); r.popFront())
            result.push_back(r.front());
        return result;
    }

    template<template<typename,typename> class X, typename R>
    X<typename R::value_type, std::allocator<typename R::value_type> > toContainer(R r)
    {
        X<typename R::value_type, std::allocator<typename R::value_type> > result;
        for (; !r.empty(); r.popFront())
            result.push_back(r.front());
        return result;
    }

    // xxx.toContainer<std::vector>()
    // xxx.toContainer<QList>()

    template<template<typename> class TLinq, typename R>
    class ToContainer_mixin
    {
        typedef typename R::value_type value_type;

    public:
        template<template<typename> class X>
        X<value_type> toContainer() const
        {
            return boolinq::toContainer<X>(((TLinq<R>*)this)->r);
        }

        template<template<typename,typename> class X>
        X<value_type, std::allocator<value_type> > toContainer() const
        {
            return boolinq::toContainer<X>(((TLinq<R>*)this)->r);
        }
    };
}
// namespace boolinq
