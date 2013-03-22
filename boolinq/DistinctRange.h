#pragma once

namespace boolinq
{
    template<typename T>
    struct JustReturn_dist
    {
        T operator()(const T & a) const
        {
            return a;
        }
    };

    template<typename R, typename F = JustReturn_dist<typename R::value_type> > 
    class DistinctRange
    {
    public:
        typedef typename R::value_type value_type;

        DistinctRange(R r, F f = JustReturn_dist<typename R::value_type>())
            : r(r), f(f)
            , fullRange(r)
            , leftIndex(0)
            , rightIndex(0)
        {
            if (isDuplicate(f(r.front()),1,0))
                popFront();
        }

        bool empty() 
        { 
            return r.empty();
        }

        value_type popFront() 
        { 
            R tmp = r;
            do 
            {
                r.popFront();
                leftIndex++;
            } while (!r.empty() && isDuplicate(f(r.front()),1,0));
            return tmp.front();
        }

        value_type popBack() 
        {
            R tmp = r;
            do
            {
                r.popBack();
                rightIndex++;
            } while (!r.empty() && isDuplicate(f(r.back()),0,1));
            return tmp.back();
        }

        value_type front() 
        { 
            return r.front();
        }

        value_type back() 
        { 
            return r.back();
        }

    private:
        template<typename T>
        bool isDuplicate(const T & value, int left, int right) const
        {
            R tmp = r;
            tmp.popFront();
            if (tmp.empty())
                return false;

            tmp = fullRange;
            for(int i = 0 ; i < leftIndex + right; i++)
            {
                if (value == f(tmp.popFront()))
                    return true;
            }

            tmp = fullRange;
            for(int i = 0 ; i < rightIndex + left; i++)
            {
                if (value == f(tmp.popBack()))
                    return true;
            }

            return false;
        }

    private:
        R r;
        F f;

        R fullRange;
        int leftIndex;
        int rightIndex;
    };

    // distinct(distinct(xxx))

    template<typename R>
    DistinctRange<R> distinct(R r)
    {
        return r;
    }

    template<typename R, typename F>
    DistinctRange<R,F> distinct(R r, F f)
    {
        return DistinctRange<R,F>(r,f);
    }

    // xxx.distinct().distinct()

    template<template<typename> class TLinq, typename R>
    class DistinctRange_mixin
    {
    public:
        TLinq<DistinctRange<R> > distinct() const
        {
            return boolinq::distinct(((TLinq<R>*)this)->r);
        }

        template<typename F>
        TLinq<DistinctRange<R,F> > distinct(F f) const
        {
            return boolinq::distinct(((TLinq<R>*)this)->r,f);
        }
    };
}
// namespace boolinq
