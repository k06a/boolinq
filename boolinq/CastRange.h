#pragma once

namespace boolinq
{
    template<typename T, typename R>
    class CastRange
    {
    public:
        typedef T value_type; 
        
        CastRange(R r)
            : r(r) 
        {
        }

        bool empty()          { return r.empty();    }
        value_type popFront() { return r.popFront(); }
        value_type popBack()  { return r.popBack();  }
        value_type front()    { return r.front();    }
        value_type back()     { return r.back();     }

    private:
        R r;
    };

    // Cast<double>(Cast<int>(xxx))

    template<typename T, typename R>
    CastRange<T,R> cast(R r)
    {
        return r;
    }

    // xxx.Cast<int>().Cast<double>()

    template<template<typename> class TLinq, typename R>
    class CastRange_mixin
    {
    public:
        template<typename T>
        TLinq<CastRange<T,R> > cast() const
        {
            return boolinq::cast<T>(((TLinq<R>*)this)->r);
        }
    };
}
// namespace boolinq
