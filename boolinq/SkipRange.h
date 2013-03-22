#pragma once

#include "Count.h"

namespace boolinq
{
    template<typename R> 
    class SkipRange
    {
    public:
        typedef typename R::value_type value_type;

        SkipRange(R rng, int n)
            : r(rng)
        {
            for (int i = 0; !r.empty() && (i < n); i++)
                r.popFront();
        }

        bool empty()          { return r.empty();    }
        value_type popFront() { return r.popFront(); }
        value_type popBack()  { return r.popBack();  }
        value_type front()    { return r.front();    }
        value_type back()     { return r.back();     }

    private:
        R r;
    };

    // skip(skip(xxx, ...), ...)

    template<typename R>
    SkipRange<R> skip(R r, int n)
    {
        return SkipRange<R>(r,n);
    }

    // xxx.skip(...).skip(...)

    template<template<typename> class TLinq, typename R>
    class SkipRange_mixin
    {
    public:
        TLinq<SkipRange<R> > skip(int n) const
        {
            return boolinq::skip(((TLinq<R>*)this)->r,n);
        }
    };
}
// namespace boolinq
