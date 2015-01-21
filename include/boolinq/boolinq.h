//
// Copyright (C) <year> <copyright holders>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//

#pragma once

#include <set>
#include <list>
#include <deque>
#include <string>
#include <vector>
#include <iostream>
#include <functional>
#include <climits>

namespace boolinq
{
    ////////////////////////////////////////////////////////////////
    // Enumerator template
    ////////////////////////////////////////////////////////////////

    class EnumeratorEndException {};

    template<typename T, typename S>
    class Enumerator
    {
        std::function<T(S&)> _nextObject;
	    S _data;

    public:
	    typedef T value_type;
	
        Enumerator(std::function<T(S&)> nextObject, S data)
            : _nextObject(nextObject)
		    , _data(data)
        {
        }

        T nextObject()
        {
            return _nextObject(_data);
        }
    };

    template<typename T, typename S>
    std::ostream & operator << (std::ostream & stream, Enumerator<T,S> enumerator)
    {
	    try
	    {
		    for (;;)
			    stream << enumerator.nextObject() << ' ';
	    }
	    catch(EnumeratorEndException &) {}
	    return stream;
    }

    ////////////////////////////////////////////////////////////////
    // Iterator and Container pair
    ////////////////////////////////////////////////////////////////

    template<typename TI, typename TC>
    class IteratorContainerPair
    {
        std::function<TI(const TC &)> get_ti;

    public:
        TC second;
        TI first;
        
        IteratorContainerPair(const TC & tc, std::function<TI(const TC &)> get_ti_)
            : get_ti(get_ti_)
            , second(tc)
            , first(get_ti(second))
        {
        }

        IteratorContainerPair(const IteratorContainerPair<TI,TC> & pair)
            : get_ti(pair.get_ti)
            , second(pair.second)
            , first(get_ti(second))
        {
            for (auto it = pair.get_ti(pair.second); it != pair.first; ++it)
                first++;
        }
    };

    ////////////////////////////////////////////////////////////////
    // Linq methods implementation
    ////////////////////////////////////////////////////////////////

    enum BytesDirection
    {
        FirstToLast,
        LastToFirst,
    };

    enum BitsDirection
    {
        HighToLow,
        LowToHigh,
    };

    template<typename TE>
    class LinqObj
    {
        typedef typename TE::value_type T;
        
        template<typename TFunc, typename TArg>
        static auto get_return_type(TFunc * func = NULL, TArg * arg1 = NULL)
            -> decltype((*func)(*arg1));

        template<typename TFunc, typename T1Arg, typename T2Arg>
        static auto get_return_type(TFunc * func = NULL, T1Arg * arg1 = NULL, T2Arg * arg2 = NULL)
            -> decltype((*func)(*arg1,*arg2));

    public:
        TE _enumerator;

        typedef typename TE::value_type value_type;

        LinqObj(TE enumerator)
            : _enumerator(enumerator)
        {
        }

        T nextObject()
        {
            return _enumerator.nextObject();
        }

        // Main methods

        void foreach_i(std::function<void(T,int)> action) const
        {
            auto en = _enumerator;
            int index = 0;
            try
            {
                for (;;)
                    action(en.nextObject(), index++);
            }
            catch(EnumeratorEndException &) {}
        }

        void foreach(std::function<void(T)> action) const
        {
            foreach_i([=](T a, int){return action(a);});
        }

        LinqObj<Enumerator<T,std::pair<TE,int> > > where_i(std::function<bool(T,int)> predicate) const
        {
            return Enumerator<T,std::pair<TE,int> >([=](std::pair<TE,int> & pair)->T{
                T object;
                do
                    object = pair.first.nextObject();
                while (!predicate(object, pair.second++));
                return object;
            }, std::make_pair(_enumerator,0));
        }

        LinqObj<Enumerator<T,std::pair<TE,int> > > where(std::function<bool(T)> predicate) const
        {
            return where_i([=](T a, int){return predicate(a);});
        }

        LinqObj<Enumerator<T,std::pair<TE,int> > > take(int count) const
        {
            return where_i([=](T, int i){return i < count;});
        }

        LinqObj<Enumerator<T,std::pair<TE,int> > > takeWhile_i(std::function<bool(T,int)> predicate) const
        {
            return Enumerator<T,std::pair<TE,int> >([=](std::pair<TE,int> & pair)->T{
                T object = pair.first.nextObject();
                if(!predicate(object,pair.second++)) throw EnumeratorEndException();
                return object;
            }, std::make_pair(_enumerator,0));
        }

        LinqObj<Enumerator<T,std::pair<TE,int> > > takeWhile(std::function<bool(T)> predicate) const
        {
            return takeWhile_i([=](T t,int){return predicate(t);});
        }

        LinqObj<Enumerator<T,std::pair<TE,int> > > skip(int count) const
        {
            return where_i([=](T, int i){return i >= count;});
        }

        LinqObj<Enumerator<T,std::pair<TE,int> > > skipWhile_i(std::function<bool(T,int)> predicate) const
        {
            return Enumerator<T,std::pair<TE,int> >([=](std::pair<TE,int> & pair)->T{
                if (pair.second != 0)
                    return pair.first.nextObject();

                T object;
                do
                    object = pair.first.nextObject();
                while (predicate(object,pair.second++));

                return object;
            }, std::make_pair(_enumerator,0));
        }

        LinqObj<Enumerator<T,std::pair<TE,int> > > skipWhile(std::function<bool(T)> predicate) const
        {
            return skipWhile_i([=](T t, int /*i*/){ return predicate(t);});
        }

        template<typename TRet>
        LinqObj<Enumerator<TRet,std::pair<TE,int> > > select_i(std::function<TRet(T,int)> transform) const
        {
            return Enumerator<TRet,std::pair<TE,int> >([=](std::pair<TE,int> & pair)->TRet{
                return transform(pair.first.nextObject(), pair.second++);
            }, std::make_pair(_enumerator,0));
        }

        template<typename TFunc>
        LinqObj<Enumerator<decltype(get_return_type<TFunc,T,int>()),std::pair<TE,int> > > select_i(TFunc transform) const
        {
            return select_i<decltype(get_return_type<TFunc,T,int>())>(transform);
        }

        template<typename TRet>
        LinqObj<Enumerator<TRet,std::pair<TE,int> > > select(std::function<TRet(T)> transform) const
        {
            return select_i<TRet>([=](T a, int){return transform(a);});
        }

        template<typename TFunc>
        LinqObj<Enumerator<decltype(get_return_type<TFunc,T>()),std::pair<TE,int> > > select(TFunc transform) const
        {
            return select<decltype(get_return_type<TFunc,T>())>(transform);
        }

        template<typename TRet>
        LinqObj<Enumerator<TRet,std::pair<TE,int> > > cast() const
        {
            return select_i<TRet>([=](T a, int){return a;});
        }

        template<typename TRet>
        LinqObj<Enumerator<T,std::pair<TE,std::set<TRet> > > > distinct(std::function<TRet(T)> transform) const
        {
            typedef std::pair<TE,std::set<TRet> > DataType;

            return Enumerator<T,DataType>([=](DataType & pair)->T{
                for (;;)
                {
                    T object = pair.first.nextObject();
                    TRet key = transform(object);
                    if (pair.second.find(key) == pair.second.end())
                    {
                        pair.second.insert(key);
                        return object;
                    } 
                }
            }, std::make_pair(_enumerator,std::set<TRet>()));
        }

        template<typename TFunc>
        LinqObj<Enumerator<T,std::pair<TE,std::set<decltype(get_return_type<TFunc,T>())> > > > distinct(TFunc transform) const
        {
            return distinct<decltype(get_return_type<TFunc,T>())>(transform);
        }


        LinqObj<Enumerator<T,std::pair<TE,std::set<T> > > > distinct() const
        {
            return distinct<T>([](T a){return a;});
        }

    protected:

        template<typename T, typename TRet>
        class transform_comparer
        {
        public:
            std::function<TRet(T)> func;
            transform_comparer(std::function<TRet(T)> func_) : func(func_) {}

            bool operator()(const T & a, const T & b) const
            {
                return func(a) < func(b);
            }
        };

    public:

        template<typename TRet>
        LinqObj<Enumerator<T,IteratorContainerPair<typename std::multiset<T,transform_comparer<T,TRet> >::iterator,
                                                   std::multiset<T,transform_comparer<T,TRet> > > > >
        orderBy(std::function<TRet(T)> transform) const
        {
            typedef IteratorContainerPair<typename std::multiset<T,transform_comparer<T,TRet> >::iterator,
                                          std::multiset<T,transform_comparer<T,TRet> > > DataType;

            std::multiset<T,transform_comparer<T,TRet> > objects(transform);
            try
            {
                auto en = _enumerator;
                for (;;)
                    objects.insert(en.nextObject());
            }
            catch(EnumeratorEndException &) {}

            return Enumerator<T,DataType>([](DataType & pair)
            {
                return (pair.first == pair.second.end())
                     ? throw EnumeratorEndException() : *(pair.first++);
            }, DataType(objects, [](const std::multiset<T,transform_comparer<T,TRet> > & mset){return mset.begin();}));
        }

        template<typename TFunc>
        LinqObj<Enumerator<T,IteratorContainerPair<typename std::multiset<T,transform_comparer<T,decltype(get_return_type<TFunc,T>())> >::iterator,
                                                   std::multiset<T,transform_comparer<T,decltype(get_return_type<TFunc,T>())> > > > >
        orderBy(TFunc transform) const
        {
            return orderBy<decltype(get_return_type<TFunc,T>())>(transform);
        }

        LinqObj<Enumerator<T,IteratorContainerPair<typename std::multiset<T,transform_comparer<T,T> >::iterator,
                                                   std::multiset<T,transform_comparer<T,T> > > > > orderBy() const
        {
            return orderBy<T>([](T a){return a;});
        }

        LinqObj<Enumerator<T,IteratorContainerPair<typename std::vector<T>::const_reverse_iterator,std::vector<T> > > > reverse() const
        {
            typedef IteratorContainerPair<typename std::vector<T>::const_reverse_iterator,std::vector<T> > DataType;

            return Enumerator<T,DataType>([](DataType & pair)
            {
                return (pair.first == pair.second.crend())
                     ? throw EnumeratorEndException() : *(pair.first++);
            }, DataType(toVector(), [](const std::vector<T> & vec){return vec.crbegin();}));
        }

        // Aggregators

        template<typename TRet>
        TRet aggregate(TRet start, std::function<TRet(TRet,T)> accumulate) const
        {
            try
            {
                auto en = _enumerator;
                for (;;)
                    start = accumulate(start, en.nextObject());
            }
            catch(EnumeratorEndException &) {}
            return start;
        }

        template<typename TRet>
        TRet sum(std::function<TRet(T)> transform) const
        {
            return aggregate<TRet>(TRet(), [=](TRet accumulator, T object){
                return accumulator + transform(object);
            });
        }

        template<typename TFunc>
        decltype(get_return_type<TFunc,T>()) sum(TFunc transform) const
        {
            return sum<decltype(get_return_type<TFunc,T>())>(transform);
        }

        template<typename TRet>
        TRet sum() const
        {
            return sum<TRet>([](T a){return a;});
        }

        T sum() const
        {
            return sum<T>();
        }

        template<typename TRet>
        TRet avg(std::function<TRet(T)> transform) const
        {
            int count = 0;
            return aggregate<TRet>(TRet(), [&](TRet accumulator, T object)->TRet{
                count++;
                return (accumulator*(count-1) + transform(object))/count;
            });
        }

        template<typename TFunc>
        decltype(get_return_type<TFunc,T>()) avg(TFunc transform) const
        {
            return avg<decltype(get_return_type<TFunc,T>())>(transform);
        }

        template<typename TRet>
        TRet avg() const
        {
            return avg<TRet>([](T a){return a;});
        }

        T avg() const
        {
            return avg<T>();
        }

        int count(std::function<bool(T)> predicate) const
        {
            return aggregate<int>(0, [=](int count, T a){return count + (predicate(a)?1:0);});
        }

        int count(const T & value) const
        {
            return count([=](T a){return a == value;});
        }

        int count() const
        {
            return count([](T){return true;});
        }

        // Bool aggregators

        bool any(std::function<bool(T)> predicate) const
        {
            try
            {
                auto en = _enumerator;
                for (;;)
                    if (predicate(en.nextObject()))
                        return true;
            }
            catch(EnumeratorEndException &) {}
            return false;
        }

        bool any() const
        {
            return any([](T a){return static_cast<bool>(a);});
        }

        bool all(std::function<bool(T)> predicate) const
        {
            return !any([=](T a){return !predicate(a);});
        }

        bool all() const
        {
            return all([](T a){return static_cast<bool>(a);});
        }

        bool contains(const T & value) const
        {
            return any([&](T a){return value == a;});
        }

        // Election aggregators

        T elect(std::function<T(T,T)> accumulate) const
        {
            auto en = _enumerator;
            T result = en.nextObject();
            try
            {
                for (;;)
                    result = accumulate(result, en.nextObject());
            }
            catch(EnumeratorEndException &) {}
            return result;
        } 

        template<typename TRet>
        T max(std::function<TRet(T)> transform) const
        {
            return elect([=](T a, T b){return transform(a) < transform(b) ? b : a;});
        }

        template<typename TFunc>
        T max(TFunc transform) const
        {
            return max<decltype(get_return_type<TFunc,T>())>(transform);
        }

        T max() const
        {
            return max<T>([](T a){return a;});
        }

        template<typename TRet>
        T min(std::function<TRet(T)> transform) const
        {
            return elect([=](T a, T b){return transform(a) < transform(b) ? a : b;});
        }

        template<typename TFunc>
        T min(TFunc transform) const
        {
            return min<decltype(get_return_type<TFunc,T>())>(transform);
        }

        T min() const
        {
            return min<T>([](T a){return a;});
        }

        // Single object returners

        T elementAt(int index) const
        {
            auto en = _enumerator;
            for (int i = 0; i < index; i++)
                en.nextObject();
            return en.nextObject();
        }

        T first(std::function<bool(T)> predicate) const
        {
            return where(predicate)._enumerator.nextObject();
        }

        T first() const
        {
            return first([](T){return true;});
        }

        T firstOrDefault(std::function<bool(T)> predicate)
        {
            try { return first(predicate); }
            catch(EnumeratorEndException &) { return T(); }
        }

        T firstOrDefault() const
        {
            try { return first(); }
            catch(EnumeratorEndException &) { return T(); }
        }

        T last(std::function<bool(T)> predicate) const
        {
            auto linq = where(predicate);
            T object = linq._enumerator.nextObject();
            try { for (;;) object = linq._enumerator.nextObject(); }
            catch(EnumeratorEndException &) { return object; }
        }

        T last() const
        {
            return last([](T){return true;});
        }

        T lastOrDefault(std::function<bool(T)> predicate) const
        {
            try { return last(predicate); }
            catch(EnumeratorEndException &) { return T(); }
        }

        T lastOrDefault() const
        {
            return lastOrDefault([](T){return true;});
        }

        // Set methods

        template<typename TE2>
        LinqObj<Enumerator<T,std::pair<bool,std::pair<TE,TE2> > > > concat(LinqObj<TE2> rhs) const
        {
            typedef std::pair<bool,std::pair<TE,TE2> > DataType;

            return Enumerator<T,DataType>([=](DataType & pair)->T{
                if (pair.first)
                    return pair.second.second.nextObject();
                try { return pair.second.first.nextObject(); }
                catch(EnumeratorEndException &) 
                {  
                    pair.first = true;
                    return pair.second.second.nextObject();
                }
            }, std::make_pair(false, std::make_pair(_enumerator, rhs._enumerator)));
        }

        // Export methods

        std::vector<T> toVector() const
        {
            std::vector<T> vec;
            try
            {
                auto en = _enumerator;
                for (;;)
                    vec.push_back(en.nextObject());
            }
            catch(EnumeratorEndException &) {}
            return vec;
        }

        std::set<T> toSet() const
        {
            std::set<T> res;
            try
            {
                auto en = _enumerator;
                for (;;)
                    res.insert(en.nextObject());
            }
            catch(EnumeratorEndException &) {}
            return res;
        }

        std::list<T> toList() const
        {
            std::list<T> res;
            try
            {
                auto en = _enumerator;
                for (;;)
                    res.push_back(en.nextObject());
            }
            catch(EnumeratorEndException &) {}
            return res;
        }

        std::deque<T> toDeque() const
        {
            std::deque<T> res;
            try
            {
                auto en = _enumerator;
                for (;;)
                    res.push_back(en.nextObject());
            }
            catch(EnumeratorEndException &) {}
            return res;
        }

        // Custom methods

        LinqObj<Enumerator<int,std::pair<int,std::pair<TE,T> > > > bytes(BytesDirection direction = FirstToLast) const
        {
            typedef std::pair<int,std::pair<TE,T> > DataType;

            auto pair = std::make_pair(_enumerator, T());
            pair.second =  pair.first.nextObject();

            return Enumerator<int,DataType>([=](DataType & pair_)->int{
                if ((direction == FirstToLast && pair_.first == sizeof(T))
                    || (direction == LastToFirst && pair_.first == -1))
                {
                    pair_.first = (direction == FirstToLast) ? 0 : sizeof(T)-1;
                    pair_.second.second = pair_.second.first.nextObject();
                }
                unsigned char * ptr = reinterpret_cast<unsigned char *>(&pair_.second.second);
                int value = ptr[pair_.first];
                pair_.first += (direction == FirstToLast) ? 1 : -1;
                return value;
            }, std::make_pair((direction == FirstToLast) ? 0 : sizeof(T)-1, pair));
        }

        template<typename TRet>
        LinqObj<Enumerator<TRet,TE> > unbytes(BytesDirection direction = FirstToLast) const
        {
            return Enumerator<TRet,TE>([=](TE & en)->TRet{
                TRet object;
                unsigned char * ptr = reinterpret_cast<unsigned char *>(&object);
                for (int i = (direction == FirstToLast) ? 0 : int(sizeof(TRet)-1);
                     i != ((direction == FirstToLast) ? int(sizeof(TRet)) : -1);
                     i += (direction == FirstToLast) ? 1 : -1)
                {
                    ptr[i] = en.nextObject();
                }
                return object;
            }, _enumerator);
        }

        LinqObj<Enumerator<int,std::pair<int,std::pair<LinqObj<Enumerator<int,std::pair<int,std::pair<TE,T> > > >,unsigned char> > > > 
        bits(BitsDirection direction = HighToLow, BytesDirection bytesDirection = FirstToLast) const
        {
            typedef std::pair<int,std::pair<LinqObj<Enumerator<int,std::pair<int,std::pair<TE,T> > > >,unsigned char> > DataType;

            auto inner = bytes(bytesDirection);
            return Enumerator<int,DataType>([=](DataType & pair)->int{
                if ((direction == LowToHigh && pair.first == CHAR_BIT)
                    || (direction == HighToLow && pair.first == -1))
                {
                    pair.first = (direction == LowToHigh) ? 0 : CHAR_BIT-1;
                    pair.second.second = static_cast<unsigned char>(pair.second.first.nextObject());
                }
                int value = 1 & (pair.second.second >> (pair.first % CHAR_BIT));
                pair.first += (direction == LowToHigh) ? 1 : -1;
                return value;
            }, std::make_pair((direction == LowToHigh) ? 0 : CHAR_BIT-1,
                              std::make_pair(inner, inner.nextObject())));
        }

        LinqObj<Enumerator<unsigned char,TE> > unbits(BitsDirection direction = HighToLow) const
        {
            return Enumerator<unsigned char,TE>([=](TE & en)->unsigned char{
                unsigned char object = 0;
                for (int i = (direction == LowToHigh) ? 0 : CHAR_BIT-1;
                         i != ((direction == LowToHigh) ? CHAR_BIT : -1);
                         i += (direction == LowToHigh) ? 1 : -1)
                {
                    object |= (en.nextObject() << i);
                }
                return object;
            }, _enumerator);
        }

        template<typename TRet>
        LinqObj<Enumerator<TRet,Enumerator<unsigned char,TE> > > unbits(BitsDirection direction = HighToLow, BytesDirection bytesDirection = FirstToLast) const
        {
            return unbits(direction).template unbytes<TRet>(bytesDirection);
        }

        template<typename TE_>
        friend std::ostream & operator << (std::ostream & stream, LinqObj<TE_> linq);
    };

    template<typename TE>
    std::ostream & operator << (std::ostream & stream, LinqObj<TE> linq)
    {
        return stream << linq._enumerator;
    }

    ////////////////////////////////////////////////////////////////
    // Linq Creators
    ////////////////////////////////////////////////////////////////

    template<typename T, typename TI>
    LinqObj<Enumerator<T,TI> > from(TI begin, TI end)
    {
        return Enumerator<T,TI>([=](TI & iter){
            return (iter == end) ? throw EnumeratorEndException() : *(iter++);
        }, begin);
    }

    template<typename T, typename TI>
    LinqObj<Enumerator<T,std::pair<TI,int> > > from(TI begin, int length) 
    {
        return Enumerator<T,std::pair<TI,int> >([=](std::pair<TI,int> & pair){
            return (pair.second++ == length) ? throw EnumeratorEndException() : *(pair.first++);
        }, std::make_pair(begin,0));
    }

    template<typename T, int N>
    auto from(T (&array)[N])
        -> decltype(from<T>(array, array + N))
    {
        return from<T>(array, array + N);
    }

    template<template<class,class> class TV, typename TT, typename TU>
    LinqObj<Enumerator<TT,IteratorContainerPair<typename TV<TT,TU>::const_iterator,TV<TT,TU> > > > from(TV<TT,TU> & container) 
    {
        typedef IteratorContainerPair<typename TV<TT,TU>::const_iterator,TV<TT,TU> > DataType;

        return Enumerator<TT,DataType>([](DataType & pair){
            return (pair.first == pair.second.cend()) ? throw EnumeratorEndException() : *(pair.first++);
        }, DataType(container, [](const TV<TT,TU> & cont){return cont.cbegin();}));
    }

    template<template<class,int> class TV, typename TT, int TL>
    LinqObj<Enumerator<TT,IteratorContainerPair<typename TV<TT,TL>::const_iterator,TV<TT,TL> > > > from(TV<TT,TL> & container)
    {
        typedef IteratorContainerPair<typename TV<TT,TL>::const_iterator,TV<TT,TL> > DataType;

        return Enumerator<TT,DataType>([](DataType & pair){
            return (pair.first == pair.second.cend()) ? throw EnumeratorEndException() : *(pair.first++);
        }, DataType(container, [](const TV<TT,TL> & cont){return cont.cbegin();}));
    }

    template<typename T>
    LinqObj<Enumerator<T,int> > repeat(T value, int count) 
    {
        return Enumerator<T,int>([=](int & index){
            return (index++ >= count) ? throw EnumeratorEndException() : value;
        },0);
    }

    template<typename T>
    LinqObj<Enumerator<T,std::pair<bool,T> > > range(T begin, T end, T step) 
    {
        return Enumerator<T,std::pair<bool,T> >([=](std::pair<bool,T> & pair){
            if (!(pair.second < end))
                throw EnumeratorEndException();
            if (!pair.first)
                pair.first = true;
            else
                pair.second += step;
            return pair.second;
        }, std::make_pair(false, begin));
    }
}
