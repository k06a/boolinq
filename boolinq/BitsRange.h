#pragma once

#include <limits.h>

#include "BytesRange.h"

namespace boolinq
{
    enum BitOrder
    {
        HighToLow,
        LowToHigh,
    };

    template<typename R, BitOrder bitOrder = HighToLow> 
    class BitsRange
    {
        typedef typename R::value_type old_value_type;

        enum 
        { 
            startBit  = (bitOrder == LowToHigh) ? 0 : (CHAR_BIT-1),
            finishBit = (bitOrder == LowToHigh) ? (CHAR_BIT-1) : 0,
            stepBit   = (bitOrder == LowToHigh) ? 1 : -1,
        };

    public:
        typedef int value_type;

        BitsRange(R rng)
            : r(rng)
            , frontBit(startBit)
            , backBit(finishBit)
            , atEnd(r.empty())
        {
        }

        bool empty()       
        {
            return atEnd;
        }

        value_type popFront()    
        {
            value_type tmp = front();
            if (checkEmpty())
                return tmp;

            if (frontBit != finishBit)
                frontBit += stepBit;
            else
            {
                frontBit = startBit;
                r.popFront(); 
            }   

            return tmp; 
        }

        value_type popBack()
        {
            value_type tmp = back();
            if (checkEmpty())
                return tmp;
            
            if (backBit != startBit)
                backBit -= stepBit;
            else
            {
                backBit = finishBit;
                r.popBack(); 
            }   

            return tmp;
        }
        
        value_type front() 
        {
            return (r.front() >> frontBit) & 1;
        }

        value_type back()  
        {
            return (r.back() >> backBit) & 1;     
        }

    private:
        bool checkEmpty()
        {
            R tmp = r;
            tmp.popFront();
            atEnd = tmp.empty() && (frontBit == backBit);
            return atEnd;
        }

    private:
        R r;
        int frontBit;
        int backBit;
        bool atEnd;
    };

    // bits(xxx)
    // bits<BitOrder>(xxx)
    // bits<BitOrder,ByteOrder>(xxx)

    template<typename R>
    BitsRange<BytesRange<R> > bits(R r)
    {
        return boolinq::bytes(r);
    }

    template<BitOrder bitOrder, typename R>
    BitsRange<BytesRange<R>,bitOrder> bits(R r)
    {
        return boolinq::bytes(r);
    }

    template<BitOrder bitOrder, ByteOrder byteOrder, typename R>
    BitsRange<BytesRange<R,byteOrder>,bitOrder> bits(R r)
    {
        return boolinq::bytes<byteOrder>(r);
    }

    // xxx.bits()
    // xxx.bits<BitOrder>()
    // xxx.bits<BitOrder,ByteOrder>()

    template<template<typename> class TLinq, typename R>
    class BitsRange_mixin
    {
    public:
        TLinq<BitsRange<BytesRange<R> > > bits() const
        {
            return boolinq::bits(((TLinq<R>*)this)->r);
        }

        template<BitOrder bitOrder>
        TLinq<BitsRange<BytesRange<R>,bitOrder> > bits() const
        {
            return boolinq::bits<bitOrder>(((TLinq<R>*)this)->r);
        }

        template<BitOrder bitOrder, ByteOrder byteOrder>
        TLinq<BitsRange<BytesRange<R,byteOrder>,bitOrder> > bits() const
        {
            return boolinq::bits<bitOrder,byteOrder>(((TLinq<R>*)this)->r);
        }
    };
}
// namespace boolinq
