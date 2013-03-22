#pragma once

#include <deque>

namespace boolinq
{
    // toVector(xxx)

    template<typename R>
    std::deque<typename R::value_type> toDeque(R r)
    {
        std::deque<typename R::value_type> result;
        for (; !r.empty(); r.popFront())
            result.push_back(r.front());
        return result;
    }

    // xxx.toVector()

    template<template<typename> class TLinq, typename R>
    class ToDeque_mixin
    {
    public:
        std::deque<typename R::value_type> toDeque() const
        {
            return boolinq::toDeque(((TLinq<R>*)this)->r);
        }
    };
}
// namespace boolinq
