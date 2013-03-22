#pragma once

namespace boolinq
{
    // contains(xxx, value)

    template<typename R, typename T>
    bool contains(R r, const T & t)
    {
        while (!r.empty())
            if (r.popFront() == t)
                return true;
        return false;
    }

    // xxx.contains(value)

    template<template<typename> class TLinq, typename R>
    class Contains_mixin
    {
    public:
        template<typename T>
        bool contains(const T & t) const
        {
            return boolinq::contains(((TLinq<R>*)this)->r,t);
        }
    };
}
// namespace boolinq
