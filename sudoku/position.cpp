//
// Created by Basuke Suzuki on 5/18/18.
//

#include "position.h"

namespace sudoku {

    bool Position::operator==(const Position& other) const
    {
        return x == other.x && y == other.y;
    }

    bool Position::operator!=(const Position& other) const
    {
        return !(*this == other);
    }

    bool Position::operator<(const Position& other) const
    {
        return y < other.y || (y == other.y && x < other.x);
    }

    bool Position::operator<=(const Position& other) const
    {
        return *this < other || *this == other;
    }

    bool Position::operator>(const Position& other) const
    {
        return !(*this <= other);
    }

    bool Position::operator>=(const Position& other) const
    {
        return !(*this < other);
    }
}

