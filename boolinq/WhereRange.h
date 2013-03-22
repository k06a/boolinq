#pragma once

namespace boolinq
{
    template<typename R, typename F> 
    class WhereRange
    {
    public:
        typedef typename R::value_type value_type;
        
        WhereRange(R r, F f)
            : r(r), f(f)
            , frontReady(false)
            , backReady(false)
        {
        }

        bool empty() 
        { 
            if (!frontReady)
                seekFront();
            return r.empty();
        }

        value_type popFront() 
        { 
            if (!frontReady)
                seekFront();

            auto tmp = *this;
            r.popFront();
            frontReady = false;
            return tmp.front();
        }

        value_type popBack() 
        {
            if (!frontReady)
                seekFront();

            auto tmp = *this;
            r.popBack();
            backReady = false;
            return tmp.back();
        }

        value_type front()
        { 
            if (!frontReady)
                seekFront();
            return r.front();
        }

        value_type back() 
        { 
            if (!backReady)
                seekBack();
            return r.back();
        }

    private:
        void seekFront()
        {
            while(!r.empty() && !f(r.front()))
                r.popFront();
            frontReady = true;
        }

        void seekBack()
        {
            while(!r.empty() && !f(r.back()))
                r.popBack();
            backReady = true;
        }

    private:
        R r;
        F f;
        bool frontReady;
        bool backReady;
    };

    // where(where(xxx, ...), ...)

    template<typename R, typename F>
    WhereRange<R,F> where(R r, F f)
    {
        return WhereRange<R,F>(r,f);
    }
    
    // xxx.where(...).where(...)

    template<template<typename> class TLinq, typename R>
    class WhereRange_mixin
    {
    public:
        template<typename F>
        TLinq<WhereRange<R,F> > where(F f) const
        {
            return boolinq::where(((TLinq<R>*)this)->r,f);
        }
    };
}
// namespace boolinq
