#pragma once

#include "BytesRange.h"

namespace boolinq
{
    template<typename R, typename T, ByteOrder byteOrder = FirstToLast> 
    class UnbytesRange
    {
        enum 
        { 
            startByte  = (byteOrder == FirstToLast) ? 0 : (sizeof(T)-1),
            finishByte = (byteOrder == FirstToLast) ? (sizeof(T)-1) : 0,
            stepByte   = (byteOrder == FirstToLast) ? 1 : -1,
        };

    public:
        typedef T value_type;

        UnbytesRange(R rng)
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
                for (int i = startByte; i != finishByte+stepByte; i += stepByte)
                    ((unsigned char*)&frontValue)[i] = r.popFront();
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
                for (int i = finishByte; i != startByte-stepByte; i -= stepByte)
                    ((unsigned char*)&backValue)[i] = r.popBack();
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

    // unbytes(xxx)
    // unbytes<ByteOrder>(xxx)

    template<typename T, typename R>
    UnbytesRange<R,T> unbytes(R r)
    {
        return r;
    }

    template<typename T, ByteOrder byteOrder, typename R>
    UnbytesRange<R,T,byteOrder> unbytes(R r)
    {
        return r;
    }

    // xxx.unbytes(...)
    // xxx.unbytes<ByteOrder>(...)

    template<template<typename> class TLinq, typename R>
    class UnbytesRange_mixin
    {
    public:
        template<typename T>
        TLinq<UnbytesRange<R,T> > unbytes() const
        {
            return boolinq::unbytes<T>(((TLinq<R>*)this)->r);
        }

        template<typename T, ByteOrder byteOrder>
        TLinq<UnbytesRange<R,T,byteOrder> > unbytes() const
        {
            return boolinq::unbytes<T,byteOrder>(((TLinq<R>*)this)->r);
        }
    };
}
// namespace boolinq
