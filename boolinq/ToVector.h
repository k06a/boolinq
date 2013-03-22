#pragma once

#include <vector>

namespace boolinq
{
    // toVector(xxx)

    template<typename R>
    std::vector<typename R::value_type> toVector(R r)
    {
        std::vector<typename R::value_type> result;
        for (; !r.empty(); r.popFront())
            result.push_back(r.front());
        return result;
    }

    // xxx.toVector()

    template<template<typename> class TLinq, typename R>
    class ToVector_mixin
    {
    public:
        std::vector<typename R::value_type> toVector() const
        {
            return boolinq::toVector(((TLinq<R>*)this)->r);
        }
    };
}
// namespace boolinq
