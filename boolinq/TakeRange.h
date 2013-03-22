#pragma once

#include "Count.h"

namespace boolinq
{
    template<typename R> 
    class TakeRange
    {
    public:
        typedef typename R::value_type value_type;

        TakeRange(R r, int n)
            : r(r), n(n), backReady(false)
        {
        }

        bool empty()          
        {
            if ((n == 0) && !backReady)
                return true;
            return r.empty();   
        }

        value_type popFront() 
        {
            n--;
            return r.popFront(); 
        }

        value_type popBack()  
        { 
            if (!backReady)
                prepareBack();
            return r.popBack(); 
        }

        value_type front()    
        { 
            return r.front();   
        }

        value_type back()    
        { 
            if (!backReady)
                prepareBack();
            return r.back();   
        }

    private:
        void prepareBack() 
        {
            int size = boolinq::count(r);
            while (size > n)
            {
                r.popBack();
                size--;
            }
            backReady = true;
        }

    private:
        R r;
        int n;
        bool backReady;
    };

    // take(take(xxx, ...), ...)

    template<typename R>
    TakeRange<R> take(R r, int n)
    {
        return TakeRange<R>(r,n);
    }

    // xxx.take(...).take(...)

    template<template<typename> class TLinq, typename R>
    class TakeRange_mixin
    {
    public:
        TLinq<TakeRange<R> > take(int n) const
        {
            return boolinq::take(((TLinq<R>*)this)->r,n);
        }
    };
}
// namespace boolinq
