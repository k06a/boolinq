#pragma once

namespace boolinq
{
    // elementAt(xxx, int)

    template<typename R>
    typename R::value_type elementAt(R r, int index)
    {
        while (index > 0)
        {
            r.popFront();
            index--;
        }
        return r.front();
    }

    // xxx.elementAt(int)

    template<template<typename> class TLinq, typename R>
    class ElementAt_mixin
    {
    public:
        typename R::value_type elementAt(int index) const
        {
            return boolinq::elementAt(((TLinq<R>*)this)->r,index);
        }
    };
}
// namespace boolinq
