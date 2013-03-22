#pragma once

#include "IterRange.h"

#include "CastRange.h"
#include "SkipRange.h"
#include "TakeRange.h"
#include "WhereRange.h"
#include "SelectRange.h"
#include "ReverseRange.h"
#include "OrderByRange.h"
#include "GroupByRange.h"
#include "DistinctRange.h"
#include "ConcatRange.h"

#include "All.h"
#include "Any.h"
#include "Sum.h"
#include "Avg.h"
#include "Min.h"
#include "Max.h"
#include "Count.h"
#include "ForEach.h"
#include "Contains.h"
#include "ElementAt.h"

#include "ToSet.h"
#include "ToList.h"
#include "ToDeque.h"
#include "ToVector.h"
#include "ToContainer.h"

#include "BytesRange.h"
#include "BitsRange.h"
#include "UnbytesRange.h"
#include "UnbitsRange.h"

namespace boolinq
{
    template<typename R>
    class Linq
        : public CastRange_mixin<Linq,R>
        , public SkipRange_mixin<Linq,R>
        , public TakeRange_mixin<Linq,R>
        , public WhereRange_mixin<Linq,R>
        , public SelectRange_mixin<Linq,R>
        , public ReverseRange_mixin<Linq,R>
        , public OrderByRange_mixin<Linq,R>
        , public GroupByRange_mixin<Linq,R>
        , public DistinctRange_mixin<Linq,R>
        , public ConcatRange_mixin<Linq,R>
        
        , public All_mixin<Linq,R>
        , public Any_mixin<Linq,R>
        , public Sum_mixin<Linq,R>
        , public Avg_mixin<Linq,R>
        , public Min_mixin<Linq,R>
        , public Max_mixin<Linq,R>
        , public Count_mixin<Linq,R>
        , public ForEach_mixin<Linq,R>
        , public Contains_mixin<Linq,R>
        , public ElementAt_mixin<Linq,R>

        , public ToSet_mixin<Linq,R>
        , public ToList_mixin<Linq,R>
        , public ToDeque_mixin<Linq,R>
        , public ToVector_mixin<Linq,R>
        , public ToContainer_mixin<Linq,R>

        , public BytesRange_mixin<Linq,R>
        , public BitsRange_mixin<Linq,R>
        , public UnbytesRange_mixin<Linq,R>
        , public UnbitsRange_mixin<Linq,R>
    {
    public:
        typedef typename R::value_type value_type;

        Linq(const R & r)
            : r(r)
        {
        }

        operator R () const
        {
            return r;
        }

        operator R & ()
        {
            return r;
        }

        bool empty()          { return r.empty();    }
        value_type popFront() { return r.popFront(); }
        value_type popBack()  { return r.popBack();  }
        value_type front()    { return r.front();    }
        value_type back()     { return r.back();     }

    public:
        R r;
    };

    //////////////////////////////////////////////////////////////////////////
    // from<CustomLinq>(xxx)
    //////////////////////////////////////////////////////////////////////////

    template<template<typename> class TLinq, typename X>
    TLinq<IterRange<typename X::const_iterator> > from(const X & x)
    {
        return range(x);
    }
    
    template<template<typename> class TLinq, typename X, const int N>
    TLinq<IterRange<const X*> > from(const X (&x)[N])
    {
        return range(x);
    }
    
    template<template<typename> class TLinq, typename X>
    TLinq<IterRange<X> > from(X b, X e)
    {
        return range(b,e);
    }
    
    template<template<typename> class TLinq, typename X>
    TLinq<IterRange<const X*> > from(const X * b, const X * e)
    {
        return range(b,e);
    }

    template<template<typename> class TLinq, typename X>
    TLinq<IterRange<const X*> > from(const X * b, int n)
    {
        return range(b,n);
    }

    //////////////////////////////////////////////////////////////////////////
    // from(xxx)
    //////////////////////////////////////////////////////////////////////////

    template<typename X>
    Linq<IterRange<typename X::const_iterator> > from(const X & x)
    {
        return from<Linq>(x);
    }

    template<typename X, const int N>
    Linq<IterRange<const X*> > from(const X (&x)[N])
    {
        return from<Linq>(x);
    }

    template<typename X>
    Linq<IterRange<X> > from(X b, X e)
    {
        return from<Linq>(b,e);
    }

    template<typename X>
    Linq<IterRange<const X*> > from(const X * b, const X * e)
    {
        return from<Linq>(b,e);
    }

    template<typename X>
    Linq<IterRange<const X*> > from(const X * b, int n)
    {
        return from<Linq>(b,n);
    }

    //////////////////////////////////////////////////////////////////////////
    // Linq equality operator for container and array
    //////////////////////////////////////////////////////////////////////////

    template<typename R, typename X>
    bool operator == (const Linq<R> & rng, const X & x)
    {
        Linq<R> tmp = rng;
        for (auto it = x.begin(); it != x.end(); ++it)
        {
            if (tmp.empty())
                return false;
            if (tmp.popFront() != *it)
                return false;
        }

        return tmp.empty();
    }

    template<typename R, typename X>
    bool operator == (const X & x, const Linq<R> & rng)
    {
        return rng == x;
    }

    template<typename R, typename X, const int N>
    bool operator == (const Linq<R> & rng, const X (&x)[N])
    {
        Linq<R> tmp = rng;
        for (int i = 0; i < N; i++)
        {
            if (tmp.empty())
                return false;
            if (tmp.popFront() != x[i])
                return false;
        }

        return tmp.empty();
    }

    template<typename R, typename X, const int N>
    bool operator == (const X (&x)[N], const Linq<R> & rng)
    {
        return rng == x;
    }
}
// namespace boolinq
