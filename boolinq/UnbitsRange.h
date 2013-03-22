#pragma once

#include "BitsRange.h"
#include "UnbytesRange.h"

namespace boolinq
{
    template<typename R, BitOrder bitOrder = HighToLow> 
    class UnbitsRange
    {
        enum 
        { 
            startBit  = (bitOrder == LowToHigh) ? 0 : (CHAR_BIT-1),
            finishBit = (bitOrder == LowToHigh) ? (CHAR_BIT-1) : 0,
            stepBit   = (bitOrder == LowToHigh) ? 1 : -1,
        };

    public:
        typedef unsigned char value_type;

        UnbitsRange(R rng)
            : r(rng)
            , frontValue()
            , backValue()
            , preEnd(r.empty())
            , atEnd(r.empty())
        {
            if (!atEnd)
            {
                popFront();
                popBack();
            }
        }

        bool empty()       
        {
            return atEnd;
        }

        value_type popFront()    
        {
            value_type tmp = front();

            if (preEnd)
            {
                atEnd = true;
                return tmp;
            }

            if (r.empty())
            {
                preEnd = true;
                frontValue = backValue;
            }
            else
            {
                frontValue = 0;
                for (int i = startBit; !r.empty() && i != finishBit+stepBit; i += stepBit)
                    frontValue |= ((r.popFront()&1) << i);
            }

            return tmp; 
        }

        value_type popBack()
        {
            value_type tmp = back();

            if (preEnd)
            {
                atEnd = true;
                return tmp;
            }

            if (r.empty())
            {
                preEnd = true;
                backValue = frontValue;
            }
            else
            {
                backValue = 0;
                for (int i = finishBit; !r.empty() && i != startBit-stepBit; i -= stepBit)
                    backValue |= ((r.popBack()&1) << i);
            }

            return tmp;
        }

        value_type front() 
        {
            return frontValue;
        }

        value_type back()  
        {
            return backValue;
        }

    private:
        R r;
        value_type frontValue;
        value_type backValue;
        bool preEnd;
        bool atEnd;
    };

    // unbits(xxx)
    // unbits<BitOrder>(xxx)
    // unbits<T>(xxx)
    // unbits<T,BitOrder>(xxx)
    // unbits<T,ByteOrder>(xxx)
    // unbits<T,BitOrder,ByteOrder>(xxx)

    template<typename R>
    UnbitsRange<R> unbits(R r)
    {
        return r;
    }

    template<BitOrder bitOrder, typename R>
    UnbitsRange<R,bitOrder> unbits(R r)
    {
        return r;
    }

    template<typename T, typename R>
    UnbytesRange<UnbitsRange<R>,T> unbits(R r)
    {
        return r;
    }

    template<typename T, BitOrder bitOrder, typename R>
    UnbytesRange<UnbitsRange<R,bitOrder>,T> unbits(R r)
    {
        return r;
    }

    //template<typename T, ByteOrder byteOrder, typename R>
    //UnbytesRange<UnbitsRange<R>,T,byteOrder> unbits(R r)
    //{
    //    return r;
    //}
    
    template<typename T, BitOrder bitOrder, ByteOrder byteOrder, typename R>
    UnbytesRange<UnbitsRange<R,bitOrder>,T,byteOrder> unbits(R r)
    {
        return r;
    }

    // xxx.unbits()
    // xxx.unbits<BitOrder>()
    // xxx.unbits<T>()
    // xxx.unbits<T,BitOrder>()
    // xxx.unbits<T,ByteOrder>()
    // xxx.unbits<T,BitOrder,ByteOrder>()

    template<template<typename> class TLinq, typename R>
    class UnbitsRange_mixin
    {
    public:
        TLinq<UnbitsRange<R> > unbits() const
        {
            return boolinq::unbits(((TLinq<R>*)this)->r);
        }

        template<BitOrder bitOrder>
        TLinq<UnbitsRange<R,bitOrder> > unbits() const
        {
            return boolinq::unbits<bitOrder>(((TLinq<R>*)this)->r);
        }

        template<typename T>
        TLinq<UnbytesRange<UnbitsRange<R>,T> > unbits() const
        {
            return boolinq::unbits<T>(((TLinq<R>*)this)->r);
        }

        template<typename T, BitOrder bitOrder>
        TLinq<UnbytesRange<UnbitsRange<R,bitOrder>,T> > unbits() const
        {
            return boolinq::unbits<T,bitOrder>(((TLinq<R>*)this)->r);
        }

        //template<typename T, ByteOrder byteOrder>
        //TLinq<UnbytesRange<UnbitsRange<R>,T,byteOrder> > unbits() const
        //{
        //    return boolinq::unbits<T,byteOrder>(((TLinq<R>*)this)->r);
        //}

        template<typename T, BitOrder bitOrder, ByteOrder byteOrder>
        TLinq<UnbytesRange<UnbitsRange<R,bitOrder>,T,byteOrder> > unbits() const
        {
            return boolinq::unbits<T,bitOrder,byteOrder>(((TLinq<R>*)this)->r);
        }
    };
}
// namespace boolinq
