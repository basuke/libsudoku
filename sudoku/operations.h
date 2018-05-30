//
// Created by Basuke Suzuki on 5/22/18.
//

#pragma once

#include <algorithm>
#include <functional>
#include <experimental/optional>


namespace sudoku {
    using std::vector;
    using std::function;
    using std::experimental::optional;
    using std::experimental::nullopt;
}

namespace sudoku::setOp {

    using std::vector;
    using std::function;

    template <typename T>
    vector<T> range(T start, int stop, int step = 0)
    {
        if (step == 0) {
            step = start <= stop ? 1 : - 1;
        }

        vector<T> result;
        if (step > 0) {
            for (int i = start; i <= stop; i += step)
                result.emplace_back(i);
        } else {
            for (int i = start; i >= stop; i += step)
                result.emplace_back(i);
        }
        return result;
    }

    template<typename T>
    bool contain(const vector<T>& src, const T& item)
    {
        return std::find(src.begin(), src.end(), item) != src.end();
    }

    template<typename T>
    void forEach(vector<T>& vec, function<void(T&)>&& task)
    {
        for (auto& item : vec) {
            task(item);
        }
    };

    template<typename T>
    vector<T> filter(const vector<T>& src, function<bool(const T& item)>&& predicate)
    {
        vector<T> result;
        for (const auto& item : src) {
            if (predicate(item))
                result.emplace_back(item);
        }
        return result;
    };

    template<typename T1, typename T2>
    vector<T2> map(const vector<T1>& vec, function<T2(const T1& item)>&& transformer)
    {
        vector<T2> result;
        for (const auto& item : vec) {
            result.emplace_back(transformer(item));
        }
        return result;
    };

    template<typename T>
    void add(vector<T>& vec, const vector<T>& other)
    {
        for (const auto& item : other) {
            if (!contain(vec, item))
                vec.emplace_back(item);
        }
        std::sort(vec.begin(), vec.end());
    }

    template<typename T>
    vector<T> merged(const vector<T>& src, const vector<T>& other)
    {
        vector<T> result { src };
        add(result, other);
        return result;
    }

    template<typename T>
    void subtract(vector<T>& vec, const vector<T>& other)
    {
        vector<T> result { };
        for (const auto& item : vec) {
            if (!contain(other, item))
                result.emplace_back(item);
        }
        vec = std::move(result);
    }

    template<typename T>
    vector<T> difference(const vector<T>& src, const vector<T>& other)
    {
        vector<T> result { src };
        subtract(result, other);
        return result;
    }

    template<typename T>
    void product(vector<T>& vec, const vector<T>& other)
    {
        vector<T> result { };
        for (const auto& item : vec) {
            if (contain(other, item))
                result.emplace_back(item);
        }
        vec = std::move(result);
    }

    template<typename T>
    vector<T> overlapped(const vector<T> &src, const vector<T> &other)
    {
        vector<T> result { src };
        product(result, other);
        return result;
    }

}