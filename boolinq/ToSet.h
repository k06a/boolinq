#pragma once

#include <set>

namespace boolinq
{
    // toSet(xxx)

    template<typename R>
    std::set<typename R::value_type> toSet(R r)
    {
        std::set<typename R::value_type> result;
        for (; !r.empty(); r.popFront())
            result.insert(r.front());
        return result;
    }

    // xxx.toSet()

    template<template<typename> class TLinq, typename R>
    class ToSet_mixin
    {
    public:
        std::set<typename R::value_type> toSet() const
        {
            return boolinq::toSet(((TLinq<R>*)this)->r);
        }
    };
}
// namespace boolinq
