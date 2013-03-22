#pragma once

namespace boolinq
{
    template<typename R>
    class ReverseRange
    {
    public:
        typedef typename R::value_type value_type; 
        
        ReverseRange(R r)
            : r(r) 
        {
        }

        bool empty()          { return r.empty();    }
        value_type popFront() { return r.popBack();  }
        value_type popBack()  { return r.popFront(); }
        value_type front()    { return r.back();     }
        value_type back()     { return r.front();    }

        template<typename R2>
        friend R2 reverse(ReverseRange<R2> r); // smart needed

    private:
        R r;
    };

    // reverse(reverse(xxx))

    template<typename R>
    ReverseRange<R> reverse(R r)
    {
        return r;
    }

    // Unwrap for double-reverse case
    template<typename R>
    R reverse(ReverseRange<R> r)
    {
        return r.r; // smart
    }

    // xxx.reverse().reverse()

    template<template<typename> class TLinq, typename R>
    class ReverseRange_mixin
    {
    public:
        TLinq<ReverseRange<R> > reverse() const
        {
            return boolinq::reverse(((TLinq<R>*)this)->r);
        }
    };

    // Unwrap for double-reverse case
    template<template<typename> class TLinq, typename T>
    class ReverseRange_mixin<TLinq,ReverseRange<T> >
    {
    public:
        TLinq<T> reverse() const
        {
            return boolinq::reverse(((TLinq<ReverseRange<T> >*)this)->r);
        }
    };
}
// namespace boolinq
