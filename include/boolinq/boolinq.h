#pragma once

#include <limits.h>

#include <functional>

#include <iterator>
#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <set>
#include <unordered_set>

//

namespace boolinq {

    struct LinqEndException {};

    enum BytesDirection {
        BytesFirstToLast,
        BytesLastToFirst,
    };

    enum BitsDirection {
        BitsHighToLow,
        BitsLowToHigh,
    };

    template<typename S, typename T>
    class Linq {
        std::function<T(S &)> nextFunc;
        S storage;

    public:
        typedef T value_type;

        Linq() : nextFunc(), storage()
        {
        }

        Linq(S storage, std::function<T(S &)> nextFunc) : nextFunc(nextFunc), storage(storage)
        {
        }

        T next()
        {
            return nextFunc(storage);
        }

        template<typename SS, typename TT>
        struct LinqIndex {
            Linq<SS, TT> linq;
            int index;
        };

        void for_each_i(std::function<void(T, int)> apply) const
        {
            LinqIndex<S, T> storage = {*this, 0};
            try {
                while (true) {
                    apply(storage.linq.next(), storage.index++);
                }
            }
            catch (LinqEndException &) {}
        }

        void for_each(std::function<void(T)> apply) const
        {
            return for_each_i([apply](T value, int index) { return apply(value); });
        }

        Linq<LinqIndex<S, T>, T> where_i(std::function<bool(T, int)> filter) const
        {
            return Linq<LinqIndex<S, T>, T>(
                {*this, 0},
                [filter](LinqIndex<S, T> &pair) {
                    while (true) {
                        T ret = pair.linq.next();
                        if (filter(ret, pair.index++)) {
                            return ret;
                        }
                    }
                }
            );
        }

        Linq<LinqIndex<S, T>, T> where(std::function<bool(T)> filter) const
        {
            return where_i([filter](T value, int index) { return filter(value); });
        }

        Linq<LinqIndex<S, T>, T> take(int count) const
        {
            return where_i([count](T /*value*/, int i) {
                if (i == count) {
                    throw LinqEndException();
                }
                return true;
            });
        }

        Linq<LinqIndex<S, T>, T> takeWhile_i(std::function<bool(T, int)> predicate) const
        {
            return where_i([predicate](T value, int i) {
                if (!predicate(value, i)) {
                    throw LinqEndException();
                }
                return true;
            });
        }

        Linq<LinqIndex<S, T>, T> takeWhile(std::function<bool(T)> predicate) const
        {
            return takeWhile_i([predicate](T value, int /*i*/) { return predicate(value); });
        }

        Linq<LinqIndex<S, T>, T> skip(int count) const
        {
            return where_i([count](T value, int i) { return i >= count; });
        }

        template<typename SS, typename TT>
        struct LinqIndexFlag {
            Linq<SS, TT> linq;
            int index;
            bool flag;
        };

        Linq<LinqIndexFlag<S, T>, T> skipWhile_i(std::function<bool(T, int)> predicate) const
        {
            return Linq<LinqIndexFlag<S, T>, T>(
                {*this, 0, false},
                [predicate](LinqIndexFlag<S, T> &tuple) {
                    if (tuple.flag) {
                        return tuple.linq.next();
                    }
                    while (true) {
                        T ret = tuple.linq.next();
                        if (!predicate(ret, tuple.index++)) {
                            tuple.flag = true;
                            return ret;
                        }
                    }
                }
            );
        }

        Linq<LinqIndexFlag<S, T>, T> skipWhile(std::function<bool(T)> predicate) const
        {
            return skipWhile_i([predicate](T value, int /*i*/) { return predicate(value); });
        }

        template<typename F, typename _TRet = typename std::result_of<F(T, int)>::type>
        Linq<LinqIndex<S, T>, _TRet> select_i(F apply) const
        {
            return Linq<LinqIndex<S, T>, _TRet>(
                {*this, 0},
                [apply](LinqIndex<S, T> &pair) {
                    return apply(pair.linq.next(), pair.index++);
                }
            );
        }

        template<typename F, typename _TRet = typename std::result_of<F(T)>::type>
        Linq<LinqIndex<S, T>, _TRet> select(F apply) const
        {
            return select_i([apply](T value, int /*index*/) { return apply(value); });
        }

        template<typename TRet>
        Linq<LinqIndex<S, T>, TRet> cast() const
        {
            return select_i([](T value, int /*i*/) { return TRet(value); });
        }

        template<typename S1, typename T1, typename S2, typename T2>
        struct LinqLinq {
            Linq<S1, T1> first;
            Linq<S2, T2> second;
            bool flag;
        };

        template<typename S2, typename T2>
        Linq<LinqLinq<S, T, S2, T2>, T> concat(const Linq<S2, T2> & rhs) const
        {
            return Linq<LinqLinq<S, T, S2, T2>, T>(
                {*this, rhs, false},
                [](LinqLinq<S, T, S2, T2> &tuple){
                    if (!tuple.flag) {
                        try {
                            return tuple.first.next();
                        }
                        catch (LinqEndException &) {}
                    }
                    return tuple.second.next();
                }
            );
        }

        template<typename SS, typename TT, typename TCurrent>
        struct LinqCurrentIndexFinished {
            Linq<SS, TT> linq;
            TCurrent current;
            int index;
            bool finished;
        };

        template<
            typename F,
            typename _TRet = typename std::result_of<F(T, int)>::type,
            typename _TRetVal = typename _TRet::value_type
        >
        Linq<LinqCurrentIndexFinished<S, T, _TRet>, _TRetVal> selectMany_i(F apply) const
        {
            return Linq<LinqCurrentIndexFinished<S, T, _TRet>, _TRetVal>(
                {*this, _TRet(), 0, true},
                [apply](LinqCurrentIndexFinished<S, T, _TRet> &tuple) {
                    while (true) {
                        if (tuple.finished) {
                            tuple.current = apply(tuple.linq.next(), tuple.index++);
                            tuple.finished = false;
                        }
                        try {
                            return tuple.current.next();
                        }
                        catch (LinqEndException &) {
                            tuple.finished = true;
                        }
                    }
                }
            );
        }

        template<
            typename F,
            typename _TRet = typename std::result_of<F(T)>::type,
            typename _TRetVal = typename _TRet::value_type
        >
        Linq<LinqCurrentIndexFinished<S, T, _TRet>, _TRetVal> selectMany(F apply) const
        {
            return selectMany_i([apply](T value, int index) { return apply(value); });
        }

        template<typename SS, typename TT, typename TKey>
        struct LinqCopyUnorderedSet {
            Linq<SS, TT> linq;
            Linq<SS, TT> linqCopy;
            std::unordered_set<TKey> set;
        };

        template<
            typename F,
            typename _TKey = typename std::result_of<F(T)>::type,
            typename _TValue = Linq<LinqIndex<S, T>, T> // where(predicate)
        >
        Linq<LinqCopyUnorderedSet<S, T, _TKey>, std::pair<_TKey, _TValue> > groupBy(F apply) const
        {
            return Linq<LinqCopyUnorderedSet<S, T, _TKey>, std::pair<_TKey, Linq<S, T> > >(
                {*this, *this, std::unordered_set<_TKey>()},
                [apply](LinqCopyUnorderedSet<S, T, _TKey> &tuple){
                    T value = tuple.linq.next();
                    _TKey key = apply(value);
                    if (tuple.set.insert(key).second) {
                        return std::make_pair(key, tuple.linqCopy.where([apply, key](T v){
                            return apply(v) == key;
                        }));
                    }
                }
            );
        }

        template<typename SS, typename TT, typename TKey>
        struct LinqUnorderedSet {
            Linq<SS, TT> linq;
            std::unordered_set<TKey> set;
        };

        template<typename F, typename _TRet = typename std::result_of<F(T)>::type>
        Linq<LinqUnorderedSet<S, T, _TRet>, T> distinct(F transform) const
        {
            return Linq<LinqUnorderedSet<S, T, _TRet>, T>(
                {*this, std::unordered_set<_TRet>()},
                [transform](LinqUnorderedSet<S, T, _TRet> &tuple) {
                    while (true) {
                        T value = tuple.linq.next();
                        if (tuple.set.insert(transform(value)).second) {
                            return value;
                        }
                    }
                }
            );
        }

        Linq<LinqUnorderedSet<S, T, T>, T> distinct() const
        {
            return distinct([](T value) { return value; });
        }

        template<typename TT>
        struct StdVectorAndIterator {
            std::vector<TT> vec;
            typename std::vector<TT>::iterator it;
        };

        template<typename F>
        Linq<StdVectorAndIterator<T>, T> orderBy(F transform) const
        {
            typedef typename std::vector<T>::iterator TIter;

            std::vector<T> items = toStdVector();
            std::sort(items.begin(), items.end(), [transform](const T &a, const T &b) {
                return transform(a) < transform(b);
            });

            return Linq<StdVectorAndIterator<T>, T>(
                {items, TIter()},
                [](StdVectorAndIterator<T> &tuple) {
                    if (tuple.it == TIter()) {
                        tuple.it = tuple.vec.begin();
                    }
                    if (tuple.it == tuple.vec.end()) {
                        throw LinqEndException();
                    }
                    return *(tuple.it++);
                }
            );
        }

        Linq<StdVectorAndIterator<T>, T> orderBy() const
        {
            return orderBy([](T value) { return value; });
        }

        template<typename TT>
        struct StdListAndReverseIterator {
            std::list<TT> list;
            typename std::list<TT>::reverse_iterator it;
        };

        Linq<StdListAndReverseIterator<T>, T> reverse() const
        {
            typedef typename std::list<T>::reverse_iterator TIter;

            std::list<T> items = toStdList();

            return Linq<StdListAndReverseIterator<T>, T>(
                {items, TIter()},
                [](StdListAndReverseIterator<T> &tuple) {
                    if (tuple.it == TIter()) {
                        tuple.it = tuple.list.rbegin();
                    }
                    if (tuple.it == tuple.list.rend()) {
                        throw LinqEndException();
                    }
                    return *(tuple.it++);
                }
            );
        }

        // Aggregators

        template<typename TRet>
        TRet aggregate(TRet start, std::function<TRet(TRet, T)> accumulate) const
        {
            Linq<S, T> linq = *this;
            try {
                while (true) {
                    start = accumulate(start, linq.next());
                }
            }
            catch (LinqEndException &) {}
            return start;
        }

        template<typename F, typename _TRet = typename std::result_of<F(T)>::type>
        _TRet sum(F transform) const
        {
            return aggregate<_TRet>(_TRet(), [transform](_TRet accumulator, T value) {
                return accumulator + transform(value);
            });
        }

        template<typename TRet = T>
        TRet sum() const
        {
            return sum([](T value) { return TRet(value); });
        }

        template<typename F, typename _TRet = typename std::result_of<F(T)>::type>
        _TRet avg(F transform) const
        {
            int count = 0;
            _TRet res = sum([transform, &count](T value) {
                count++;
                return transform(value);
            });
            return res / count;
        }

        template<typename TRet = T>
        TRet avg() const
        {
            return avg([](T value) { return TRet(value); });
        }

        int count() const
        {
            int index = 0;
            for_each([&index](T /**/a) { index++; });
            return index;
        }

        int count(std::function<bool(T)> predicate) const
        {
            return where(predicate).count();
        }

        int count(const T &item) const
        {
            return count([item](T value) { return item == value; });
        }

        // Bool aggregators

        bool any(std::function<bool(T)> predicate) const
        {
            Linq<S, T> linq = *this;
            try {
                while (true) {
                    if (predicate(linq.next()))
                        return true;
                }
            }
            catch (LinqEndException &) {}
            return false;
        }

        bool any() const
        {
            return any([](T value) { return static_cast<bool>(value); });
        }

        bool all(std::function<bool(T)> predicate) const
        {
            return !any([predicate](T value) { return !predicate(value); });
        }

        bool all() const
        {
            return all([](T value) { return static_cast<bool>(value); });
        }

        bool contains(const T &item) const
        {
            return any([&item](T value) { return value == item; });
        }

        // Election aggregators

        T elect(std::function<T(T, T)> accumulate) const
        {
            Linq<S, T> linq = *this;
            T result;
            try {
                result = linq.next();
                while (true) {
                    result = accumulate(result, linq.next());
                }
            }
            catch (LinqEndException &) {}
            return result;
        }

        template<typename F>
        T max(F transform) const
        {
            return elect([transform](const T &a, const T &b) {
                return (transform(a) < transform(b)) ? b : a;
            });
        }

        T max() const
        {
            return max([](T value) { return value; });
        }

        template<typename F>
        T min(F transform) const
        {
            return elect([transform](const T &a, const T &b) {
                return (transform(a) < transform(b)) ? a : b;
            });
        }

        T min() const
        {
            return min([](T value) { return value; });
        }

        // Single object returners

        T elementAt(int index) const
        {
            return skip(index).next();
        }

        T first(std::function<bool(T)> predicate) const
        {
            return where(predicate).next();
        }

        T first() const
        {
            return next();
        }

        T firstOrDefault(std::function<bool(T)> predicate) const
        {
            try {
                return where(predicate).next();
            }
            catch (LinqEndException &) {}
            return T();
        }

        T firstOrDefault() const
        {
            firstOrDefault([](T /*value*/) { return true; });
        }

        T last(std::function<bool(T)> predicate) const
        {
            T res;
            for_each([&res](T value) {
                res = value;
            });
            return res;
        }

        T last() const
        {
            return last([](T /*value*/) { return true; });
        }

        T lastOrDefault(std::function<bool(T)> predicate) const
        {
            try {
                return last(predicate);
            }
            catch (LinqEndException &) {}
            return T();
        }

        T lastOrDefault() const
        {
            return lastOrDefault([](T  /*value*/) { return true; });
        }

        // Export to containers

        std::vector<T> toStdVector() const
        {
            std::vector<T> items;
            for_each([&items](T value) {
                items.push_back(value);
            });
            return items;
        }

        std::list<T> toStdList() const
        {
            std::list<T> items;
            for_each([&items](T value) {
                items.push_back(value);
            });
            return items;
        }

        std::deque<T> toStdDeque() const
        {
            std::deque<T> items;
            for_each([&items](T value) {
                items.push_back(value);
            });
            return items;
        }

        std::set<T> toStdSet() const
        {
            std::set<T> items;
            for_each([&items](T value) {
                items.insert(value);
            });
            return items;
        }

        std::unordered_set<T> toStdUnorderedSet() const
        {
            std::unordered_set<T> items;
            for_each([&items](T value) {
                items.insert(value);
            });
            return items;
        }

        // Bits and bytes

        template<typename SS, typename TT>
        struct LinqBytesBitsValueIndex{
            Linq<SS, TT> linq;
            BytesDirection bytesDirection;
            BitsDirection bitsDirection;
            TT value;
            int index;
        };

        Linq<LinqBytesBitsValueIndex<S, T>, int> bytes(BytesDirection direction = BytesFirstToLast) const
        {
            return Linq<LinqBytesBitsValueIndex<S, T>, int>(
                 {*this, direction, BitsHighToLow, T(), sizeof(T)},
                 [](LinqBytesBitsValueIndex<S, T> &tuple) {
                      if (tuple.index == sizeof(T)) {
                          tuple.value = tuple.linq.next();
                          tuple.index = 0;
                      }

                      unsigned char *ptr = reinterpret_cast<unsigned char *>(&tuple.value);

                      int byteIndex = tuple.index;
                      if (tuple.bytesDirection == BytesLastToFirst) {
                          byteIndex = sizeof(T) - 1 - byteIndex;
                      }

                     tuple.index++;
                     return ptr[byteIndex];
                 }
            );
        }

        template<typename TRet>
        Linq<LinqBytesBitsValueIndex<S, T>, TRet> unbytes(BytesDirection direction = BytesFirstToLast) const
        {
            return Linq<LinqBytesBitsValueIndex<S, T>, TRet>(
                 {*this, direction, BitsHighToLow, T(), 0},
                 [](LinqBytesBitsValueIndex<S, T> &tuple) {
                     TRet value;
                     unsigned char *ptr = reinterpret_cast<unsigned char *>(&value);

                     for (int i = 0; i < sizeof(TRet); i++) {
                         int byteIndex = i;
                         if (tuple.bytesDirection == BytesLastToFirst) {
                             byteIndex = sizeof(TRet) - 1 - byteIndex;
                         }

                         ptr[byteIndex] = tuple.linq.next();
                     }

                     return value;
                 }
            );
        }

        Linq<LinqBytesBitsValueIndex<S, T>, int> bits(BitsDirection bitsDir = BitsHighToLow, BytesDirection bytesDir = BytesFirstToLast) const
        {
            return Linq<LinqBytesBitsValueIndex<S, T>, int>(
                 {*this, bytesDir, bitsDir, T(), sizeof(T) * CHAR_BIT},
                 [](LinqBytesBitsValueIndex<S, T> &tuple) {
                      if (tuple.index == sizeof(T) * CHAR_BIT) {
                          tuple.value = tuple.linq.next();
                          tuple.index = 0;
                      }

                      unsigned char *ptr = reinterpret_cast<unsigned char *>(&tuple.value);

                      int byteIndex = tuple.index / CHAR_BIT;
                      if (tuple.bytesDirection == BytesLastToFirst) {
                          byteIndex = sizeof(T) - 1 - byteIndex;
                      }

                     int bitIndex = tuple.index % CHAR_BIT;
                     if (tuple.bitsDirection == BitsHighToLow) {
                         bitIndex = CHAR_BIT - 1 - bitIndex;
                     }

                     tuple.index++;
                     return (ptr[byteIndex] >> bitIndex) & 1;
                 }
            );
        }

        template<typename TRet = unsigned char>
        Linq<LinqBytesBitsValueIndex<S, T>, TRet> unbits(BitsDirection bitsDir = BitsHighToLow, BytesDirection bytesDir = BytesFirstToLast) const
        {
            return Linq<LinqBytesBitsValueIndex<S, T>, TRet>(
                 {*this, bytesDir, bitsDir, T(), 0},
                 [](LinqBytesBitsValueIndex<S, T> &tuple) {
                     TRet value = TRet();
                     unsigned char *ptr = reinterpret_cast<unsigned char *>(&value);

                     for (int i = 0; i < sizeof(TRet) * CHAR_BIT; i++) {
                         int byteIndex = i / CHAR_BIT;
                         if (tuple.bytesDirection == BytesLastToFirst) {
                             byteIndex = sizeof(TRet) - 1 - byteIndex;
                         }

                         int bitIndex = i % CHAR_BIT;
                         if (tuple.bitsDirection == BitsHighToLow) {
                             bitIndex = CHAR_BIT - 1 - bitIndex;
                         }

                         if (tuple.linq.next()) {
                             ptr[byteIndex] |= (1 << bitIndex);
                         } else {
                             ptr[byteIndex] &= (~0 ^ (1 << bitIndex));
                         }
                     }

                     return value;
                 }
            );
        }
    };

    template<typename S, typename T>
    std::ostream &operator<<(std::ostream &stream, Linq<S, T> linq)
    {
        try {
            while (true) {
                stream << linq.next() << ' ';
            }
        }
        catch (LinqEndException &) {}
        return stream;
    }

    ////////////////////////////////////////////////////////////////
    // Linq Creators
    ////////////////////////////////////////////////////////////////

    template<typename T>
    Linq<std::pair<T, T>, typename std::iterator_traits<T>::value_type> from(T begin, T end)
    {
        return Linq<std::pair<T, T>, typename std::iterator_traits<T>::value_type>(
            {begin, end},
            [](std::pair<T, T> &pair) {
                if (pair.first == pair.second) {
                    throw LinqEndException();
                }
                return *(pair.first++);
            }
        );
    }

    template<typename T>
    Linq<std::pair<T, T>, typename std::iterator_traits<T>::value_type> from(T it, int n)
    {
        return from(it, it + n);
    }

    template<typename T, int N>
    Linq<std::pair<T *, T *>, T> from(T (&array)[N])
    {
        return from((T *)(&array), (T *)(&array) + N);
    }

    template<template<class> class TV, typename TT>
    auto from(const TV<TT> & container)
        -> decltype(from(std::begin(container), std::end(container)))
    {
        return from(std::begin(container), std::end(container));
    }

    // std::list, std::vector, std::dequeue
    template<template<class, class> class TV, typename TT, typename TU>
    auto from(const TV<TT, TU> & container)
        -> decltype(from(std::begin(container), std::end(container)))
    {
        return from(std::begin(container), std::end(container));
    }

    // std::set
    template<template<class, class, class> class TV, typename TT, typename TS, typename TU>
    auto from(const TV<TT, TS, TU> & container)
        -> decltype(from(std::begin(container), std::end(container)))
    {
        return from(std::begin(container), std::end(container));
    }

    // std::map
    template<template<class, class, class, class> class TV, typename TK, typename TT, typename TS, typename TU>
    auto from(const TV<TK, TT, TS, TU> & container)
        -> decltype(from(std::begin(container), std::end(container)))
    {
        return from(std::begin(container), std::end(container));
    }

    // std::array
    template<template<class, size_t> class TV, typename TT, size_t TL>
    auto from(const TV<TT, TL> & container)
        -> decltype(from(std::begin(container), std::end(container)))
    {
        return from(std::begin(container), std::end(container));
    }

    template<typename T>
    Linq<std::pair<T, int>, T> repeat(T value, int count) {
        return Linq<std::pair<T, int>, T>(
            {value, count},
            [](std::pair<T, int> &pair) {
                if (pair.second > 0) {
                    pair.second--;
                    return pair.first;
                }
                throw LinqEndException();
            }
        );
    }

    template<typename T>
    Linq<std::pair<std::pair<T, T>, T>, T> range(T start, T end, T step) {
        return Linq<std::pair<std::pair<T, T>, T>, T>(
            {{start, end}, step},
            [](std::pair<std::pair<T, T>, T> &tuple) {
                if (tuple.first.first < tuple.first.second) {
                    return *(tuple.first.first += tuple.second);
                }
                throw LinqEndException();
            }
        );
    }
}