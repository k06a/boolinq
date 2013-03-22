#pragma once

#include "DistinctRange.h"
#include "WhereRange.h"

namespace boolinq
{
    template<typename F, typename TArg>
    static auto get_return_type_gb(F * f = NULL, TArg * arg = NULL)
                -> decltype((*f)(*arg));

    template<typename T>
    struct JustReturn_gb
    {
        T operator()(const T & a) const
        {
            return a;
        }
    };

    template<typename T, typename F>
    struct ReturnEquals_gb
    {
        typedef decltype(get_return_type_gb<F,T>()) value_type;

        ReturnEquals_gb(const T & val, F f)
            : val(f(val)), f(f)
        {
        }

        bool operator()(const T & a) const
        {
            return val == f(a);
        }

    private:
        value_type val;
        F f;
    };

    template<typename R, typename F> 
    class WhereRange_withKey : public WhereRange<R, ReturnEquals_gb<typename R::value_type,F> >
    {
    public:
        typedef typename R::value_type value_type;
        typedef decltype(get_return_type_gb<F,value_type>()) TKey;

        WhereRange_withKey(R r, F f, const value_type & key)
            : WhereRange(r, ReturnEquals_gb<value_type,F>(key,f))
            , k(f(key))
        {
        }

        const TKey & key() const
        {
            return k;
        }

    private:
        TKey k;
    };

    //////////////////////////////////////////////////////////////////////////

    template<typename R, typename F = JustReturn_gb<typename R::value_type> > 
    class GroupByRange
    {
    public:
        typedef typename R::value_type r_value_type;
        typedef WhereRange_withKey<R,F> value_type;

        GroupByRange(R r, F f = JustReturn_gb<r_value_type>())
            : r(r), dr(r,f), f(f)
            , _front(r,f,dr.front())
            , _back(r,f,dr.back())
        {
        }

        bool empty() 
        { 
            return dr.empty();
        }

        value_type popFront()             
        { 
            DistinctRange<R,F> tmp = dr;
            dr.popFront();
            if ((!empty()))
                _front = value_type(r,f,dr.front());
            return value_type(r,f,tmp.front());
        }

        value_type popBack()
        {
            DistinctRange<R,F> tmp = dr;
            dr.popBack();
            if ((!empty()))
                _back = value_type(r,f,dr.back());
            return value_type(r,f,tmp.back());
        }

        value_type & front()
        { 
            return _front;
        }

        value_type & back()
        { 
            return _back;
        }

    private:
        R r;
        DistinctRange<R,F> dr;
        F f;

        value_type _front;
        value_type _back;
    };

    // groupBy(groupBy(xxx, ...), ...)

    template<typename R, typename F>
    GroupByRange<R,F> groupBy(R r, F f)
    {
        return GroupByRange<R,F>(r,f);
    }

    // xxx.groupBy(...).groupBy(...)

    template<template<typename> class TLinq, typename R>
    class GroupByRange_mixin
    {
    public:
        template<typename F>
        TLinq<GroupByRange<R,F> > groupBy(F f) const
        {
            return boolinq::groupBy(((TLinq<R>*)this)->r,f);
        }
    };
}
// namespace boolinq
