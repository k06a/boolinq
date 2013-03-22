#pragma once

namespace boolinq
{
    enum ByteOrder
    {
        FirstToLast,
        LastToFirst,
    };

    template<typename R, ByteOrder byteOrder = FirstToLast> 
    class BytesRange
    {
        typedef typename R::value_type old_value_type;
        enum 
        { 
            startByte  = (byteOrder == FirstToLast) ? 0 : (sizeof(old_value_type)-1),
            finishByte = (byteOrder == FirstToLast) ? (sizeof(old_value_type)-1) : 0,
            stepByte   = (byteOrder == FirstToLast) ? 1 : -1,
        };

    public:
        typedef unsigned char value_type;

        BytesRange(R rng)
            : r(rng)
            , frontByte(startByte)
            , backByte(finishByte)
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

            if (frontByte != finishByte)
                frontByte += stepByte;
            else
            {
                frontByte = startByte;
                r.popFront();
            }   

            return tmp; 
        }

        value_type popBack()
        {
            value_type tmp = back();
            if (checkEmpty())
                return tmp;

            if (backByte != startByte)
                backByte -= stepByte;
            else
            {
                backByte = finishByte;
                r.popBack();
            }   

            return tmp;
        }

        value_type front() 
        {
            old_value_type val = r.front();
            return ((unsigned char *)&val)[frontByte];
        }

        value_type back()  
        {
            old_value_type val = r.back();
            return ((unsigned char *)&val)[backByte];     
        }

    private:
        bool checkEmpty()
        {
            R tmp = r;
            tmp.popFront();
            atEnd = tmp.empty() && (frontByte == backByte);
            return atEnd;
        }

    private:
        R r;
        int frontByte;
        int backByte;
        bool atEnd;
    };

    // bytes(xxx)
    // bytes<ByteOrder>(xxx)

    template<typename R>
    BytesRange<R> bytes(R r)
    {
        return r;
    }

    template<ByteOrder byteOrder, typename R>
    BytesRange<R,byteOrder> bytes(R r)
    {
        return r;
    }

    // xxx.bytes(...)
    // xxx.bytes<ByteOrder>(...)

    template<template<typename> class TLinq, typename R>
    class BytesRange_mixin
    {
    public:
        TLinq<BytesRange<R> > bytes() const
        {
            return boolinq::bytes(((TLinq<R>*)this)->r);
        }

        template<ByteOrder byteOrder>
        TLinq<BytesRange<R,byteOrder> > bytes() const
        {
            return boolinq::bytes<byteOrder>(((TLinq<R>*)this)->r);
        }
    };
}
// namespace boolinq
