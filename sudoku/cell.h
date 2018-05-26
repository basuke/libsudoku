//
// Created by Basuke Suzuki on 5/21/18.
//

#pragma once

#include "position.h"
#include <set>
#include <vector>

namespace sudoku {

    class Cell {
        Position pos;

    public:
        mutable int number;
        int x() const { return pos.x; }
        int y() const { return pos.y; }

        Cell() = delete;
        Cell(int x, int y, int number = 0) : pos {x, y}, number {number} {
            assert(number >= 0 && number <= 9);
        }
        explicit Cell(const Position& pos, int number = 0) : pos {pos}, number {number} {
            assert(number >= 0 && number <= 9);
        }

        Cell(const Cell&) = default;
        Cell& operator=(const Cell&) = default;

        Cell& operator=(int number);

        bool operator==(const Cell& other) const;
        bool operator!=(const Cell& other) const;

        bool operator<(const Cell& other) const;
        bool operator<=(const Cell& other) const;

        bool operator>(const Cell& other) const;
        bool operator>=(const Cell& other) const;

        bool operator==(const Position& other) const;
        bool operator!=(const Position& other) const;

        bool operator<(const Position& other) const;
        bool operator<=(const Position& other) const;

        bool operator>(const Position& other) const;
        bool operator>=(const Position& other) const;

        bool operator==(int number) const { return this->number == number; }
        bool operator!=(int number) const { return !(*this == number); }
        explicit operator bool() const { return number > 0; }

        const Position& position() const;
    };

    using Cells = std::set<Cell>;

    bool contain(const Cells& cells, const Cell& cell);

    Cells add(const Cells& cells, const Cell& cell);
    Cells add(const Cells& cells, const Cells& other);
    Cells subtract(const Cells& cells, const Cell& cell);
    Cells subtract(const Cells& cells, const Cells& other);
    Cells cross(const Cells& a, const Cells& b);

    using CellPredicate = std::function<bool(const Cell&)>;

    Cells filter(const Cells& cells, CellPredicate&& predicate);

    bool isEmpty(const Cell& cell);
    bool hasNumber(const Cell& cell);
};


