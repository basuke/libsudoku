//
// Created by Basuke Suzuki on 5/11/18.
//

#pragma once

#include <array>
#include <string>
#include <experimental/optional>

using std::array;
using std::string;
using std::experimental::optional;
using std::experimental::nullopt;

namespace sudoku {

    class Parser {
    public:
        explicit Parser(const string&);
        optional<array<int, 9 * 9>> result() const;

    private:
        array<int, 9 * 9> numbers;
        bool success { };

        bool parse(const string&);
    };


    optional<array<int, 9 * 9>> parse(const string&);
}
