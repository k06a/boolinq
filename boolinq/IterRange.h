#pragma once

#include <iterator>
#include <assert.h>

namespace boolinq
{
    template<typename TIter> 
    class IterRange
    {
    public:
        typedef typename std::iterator_traits<TIter>::value_type value_type;
        
        IterRange(TIter b, TIter e)
            : b(b), e(e)
        {
        }

        bool empty()
        {
            return (b == e);
        }

        value_type popFront()
        {
            assert(!empty());
            return *(b++);
        }

        value_type popBack()
        {
            assert(!empty());
            return *(--e);
        }

        value_type front()
        {
            assert(!empty());
            return *b;
        }

        value_type back()
        {
            assert(!empty());
            TIter tmp = e;
            return *(--tmp);
        }

    private:
        TIter b;
        TIter e;
    };

    //////////////////////////////////////////////////////////////////////

    template<typename T>
    IterRange<typename T::const_iterator> range(const T & vec)
    {
        return IterRange<typename T::const_iterator>(vec.begin(), vec.end());
    }
    
    template<typename T, const int N>
    IterRange<const T*> range(const T (&arr)[N])
    {
        return IterRange<const T*>((const T*)arr, (const T*)arr+N);
    }

    template<typename T>
    IterRange<T> range(T b, T e)
    {
        return IterRange<T>(b,e);
    }
    
    template<typename T>
    IterRange<const T*> range(const T * b, const T * e)
    {
        return IterRange<const T*>(b,e);
    }

    template<typename T>
    IterRange<const T*> range(const T * b, int n)
    {
        return IterRange<const T*>(b,b+n);
    }
}
// namespace boolinq
