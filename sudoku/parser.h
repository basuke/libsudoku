//
// Created by Basuke Suzuki on 5/11/18.
//

#pragma once

#include "sudoku.h"

namespace sudoku {

    class Parser {
    public:
        explicit Parser(const std::string&);
        optional<Board> result() const;

    private:
        Board board;
        bool success { };

        bool parse(const std::string&);
    };

    optional<Board> parse(const std::string&);
}
