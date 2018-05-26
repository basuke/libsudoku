//
// Created by Basuke Suzuki on 5/22/18.
//

#pragma once

#include <algorithm>

namespace {

    template<typename Container, typename T>
    Container<T> filter(const Container<T>& container, std::function<bool(const T& item)> predicate) {
        Container<T> result;
        return result;
    };
}