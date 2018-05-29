//
// Created by Basuke Suzuki on 5/22/18.
//

#pragma once

#include <algorithm>
#include <set>
#include <functional>
#include <experimental/optional>


namespace sudoku {
    using std::set;
    using std::vector;
    using std::function;
    using std::experimental::optional;
    using std::experimental::nullopt;
}

namespace sudoku::setOp {

    using std::set;
    using std::function;

    template<typename T>
    bool contain(const set<T>& src, const T& item)
    {
        return src.find(item) != src.end();
    }

    template<typename T>
    set<T> filter(const set<T>& src, function<bool(const T& item)> predicate)
    {
        set<T> result;
        for (const auto& item : src) {
            if (predicate(item))
                result.insert(item);
        }
        return result;
    };

    template<typename T1, typename T2>
    set<T2> transform(const set<T1>& src, function<T2(const T1& item)> transformer)
    {
        set<T2> result;
        for (const auto& item : src) {
            result.insert(transformer(item));
        }
        return result;
    };

    template<typename T>
    set<T> add(const set<T>& src, const set<T>& other)
    {
        set<T> result { src };
        for (const auto& item : other) {
            result.insert(item);
        }
        return result;
    }

    template<typename T>
    set<T> add(const set<T>& src, const T& item)
    {
        set<T> result { src };
        result.insert(item);
        return result;
    }

    template<typename T>
    set<T> subtract(const set<T>& src, const set<T>& other)
    {
        set<T> result { src };
        for (const auto& item : other) {
            result.erase(item);
        }
        return result;
    }

    template<typename T>
    set<T> subtract(const set<T>& src, const T& item)
    {
        set<T> result { src };
        result.erase(item);
        return result;
    }

    template<typename T>
    set<T> overlap(const set<T> &src, const set<T> &other)
    {
        set<T> result { };
        for (const auto& item : other) {
            if (contain(src, item))
                result.insert(item);
        }
        return result;
    }

}