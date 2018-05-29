//
// Created by Basuke Suzuki on 5/21/18.
//

#pragma once

#include "position.h"
#include <set>
#include <vector>

namespace sudoku {

    using std::function;
    using std::set;
    using std::vector;

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

        Cell with(int number) const;

        // Predicates

        static bool isEmpty(const Cell& cell);
        static bool hasNumber(const Cell& cell);
    };

    using Cells = set<Cell>;
    using CellPredicate = function<bool(const Cell&)>;

    set<int> numbersInCells(const Cells& cells);

};


