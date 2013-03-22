#pragma once

#include <list>

namespace boolinq
{
    // toList(xxx)

    template<typename R>
    std::list<typename R::value_type> toList(R r)
    {
        std::list<typename R::value_type> result;
        for (; !r.empty(); r.popFront())
            result.push_back(r.front());
        return result;
    }

    // xxx.toList()

    template<template<typename> class TLinq, typename R>
    class ToList_mixin
    {
    public:
        std::list<typename R::value_type> toList() const
        {
            return boolinq::toList(((TLinq<R>*)this)->r);
        }
    };
}
// namespace boolinq
