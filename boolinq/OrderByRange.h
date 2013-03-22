#pragma once

#include "Count.h"

namespace boolinq
{
    template<typename T>
    struct JustReturn
    {
        T operator()(const T & a) const
        {
            return a;
        }
    };

    template<typename R, typename F = JustReturn<typename R::value_type> > 
    class OrderByRange
    {
    public:
        typedef typename R::value_type value_type;

        OrderByRange(R r, F f = JustReturn<typename R::value_type>())
            : r(r), f(f)
            , atEnd(false)
            , size(boolinq::count(r))
            , minimumValue(r)
            , maximumValue(r)
            , minimumIndex(0)
            , maximumIndex(0)
        {
            seekFirstMin();
            seekFirstMax();
            atEnd = (minimumIndex + maximumIndex == size);
        }

        bool empty() 
        { 
            return atEnd;
        }

        value_type popFront() 
        { 
            R tmp = minimumValue;
            seekNextMin();
            return tmp.front();
        }

        value_type popBack() 
        {
            R tmp = maximumValue;
            seekNextMax();
            return tmp.back();
        }

        value_type front() 
        { 
            return minimumValue.front();
        }

        value_type back() 
        { 
            return maximumValue.back();
        }

    private:
        void seekFirstMin()
        {
            R currentValue = r;
            int currentIndex = 0;
            
            while(!currentValue.empty())
            {
                if (f(currentValue.front()) < f(minimumValue.front()))
                {
                    minimumValue = currentValue;
                    minimumIndex = currentIndex;
                }

                currentValue.popFront();
                currentIndex++;
            }
        }

        void seekFirstMax()
        {
            R currentValue = r;
            int currentIndex = 0;

            while(!currentValue.empty())
            {
                if (f(maximumValue.back()) < f(currentValue.back()))
                {
                    maximumValue = currentValue;
                    maximumIndex = currentIndex;
                }

                currentValue.popBack();
                currentIndex++;
            }
        }

        void seekNextMin()
        {
            if (minimumIndex + maximumIndex + 1 == size)
            {
                atEnd = true;
                return;
            }

            R cur_value = r;
            R min_value = minimumValue;
            int cur_index = 0;
            int min_index = minimumIndex;

            while(!cur_value.empty())
            {
                if ((f(cur_value.front()) < f(minimumValue.front()))
                    || (f(cur_value.front()) == f(minimumValue.front())
                        && cur_index <= minimumIndex))
                {
                    cur_value.popFront();
                    cur_index++;
                    continue;
                }

                if (min_index == minimumIndex
                    && cur_index != minimumIndex)
                {
                    min_value = cur_value;
                    min_index = cur_index;
                }
                
                if (f(cur_value.front()) < f(min_value.front()))       
                {
                    min_value = cur_value;
                    min_index = cur_index;
                }

                if (f(cur_value.front()) == f(minimumValue.front())
                    && minimumIndex < cur_index)
                {
                    minimumValue = cur_value;
                    minimumIndex = cur_index;
                    return;

                }

                cur_value.popFront();
                cur_index++;
            }

            minimumValue = min_value;
            minimumIndex = min_index;
        }

        void seekNextMax()
        {
            if (minimumIndex + maximumIndex + 1 == size)
            {
                atEnd = true;
                return;
            }

            R cur_value = r;
            R max_value = maximumValue;
            int cur_index = 0;
            int max_index = maximumIndex;

            while(!cur_value.empty())
            {
                if ((f(maximumValue.back()) < f(cur_value.back()))
                    || (f(cur_value.back()) == f(maximumValue.back())
                        && cur_index <= maximumIndex))
                {
                    cur_value.popBack();
                    cur_index++;
                    continue;
                }

                if (max_index == maximumIndex
                    && cur_index != maximumIndex)
                {
                    max_value = cur_value;
                    max_index = cur_index;
                }

                if (f(max_value.back()) < f(cur_value.back()))
                {
                    max_value = cur_value;
                    max_index = cur_index;
                }

                if (f(cur_value.back()) == f(maximumValue.back())
                    && maximumIndex < cur_index)
                {
                    maximumValue = max_value;
                    maximumIndex = max_index;
                    return;
                }

                cur_value.popBack();
                cur_index++;
            }

            maximumValue = max_value;
            maximumIndex = max_index;  
        }

    private:
        R r;
        F f;

        bool atEnd;
        int size;
        R minimumValue;
        R maximumValue;
        int minimumIndex;
        int maximumIndex;
    };

    // orderBy(orderBy(xxx, ...), ...)

    template<typename R>
    OrderByRange<R> orderBy(R r)
    {
        return r;
    }

    template<typename R, typename F>
    OrderByRange<R,F> orderBy(R r, F f)
    {
        return OrderByRange<R,F>(r,f);
    }

    // xxx.orderBy(...).orderBy(...)

    template<template<typename> class TLinq, typename R>
    class OrderByRange_mixin
    {
    public:
        TLinq<OrderByRange<R> > orderBy() const
        {
            return boolinq::orderBy(((TLinq<R>*)this)->r);
        }

        template<typename F>
        TLinq<OrderByRange<R,F> > orderBy(F f) const
        {
            return boolinq::orderBy(((TLinq<R>*)this)->r,f);
        }
    };
}
// namespace boolinq
