//
// Created by Basuke Suzuki on 5/18/18.
//

#pragma once

#include <cassert>

namespace sudoku {

    struct Position {
        using is_transparent = void;

        int x;
        int y;

        Position() = delete;

        Position(int x, int y) : x(x), y(y) {
            assert(x >= 1 && x <= 9 && y >= 1 && y <= 9);
        }

        Position(const Position &) = default;

        Position &operator=(const Position &) = default;

        bool operator==(const Position &other) const;

        bool operator!=(const Position &other) const;

        bool operator<(const Position &other) const;

        bool operator<=(const Position &other) const;

        bool operator>(const Position &other) const;

        bool operator>=(const Position &other) const;
    };
}
