//
// Created by Basuke Suzuki on 5/23/18.
//

#pragma once

#include <set>
#include <vector>

namespace sudoku {

    template <typename T>
    std::vector<T> setToVector(const std::set<T>& src)
    {
        std::vector<T> result;
        std::copy(src.begin(), src.end(), back_inserter(result));
        return result;
    }

    template <typename T>
    std::set<T> vectorToSet(const std::vector<T>& src)
    {
        std::set<T> result;
        std::copy(src.begin(), src.end(), inserter(result, result.begin()));
        return result;
    }

    template <typename T>
    std::vector<T> range(T start, int stop, int step = 0)
    {
        if (step == 0) {
            step = start <= stop ? 1 : - 1;
        }

        std::vector<T> result;
        if (step > 0) {
            for (int i = start; i <= stop; i += step)
                result.emplace_back(i);
        } else {
            for (int i = start; i >= stop; i += step)
                result.emplace_back(i);
        }
        return result;
    }

}