//
// Created by Basuke Suzuki on 5/21/18.
//

#include "cell.h"
#include "operations.h"

namespace sudoku {

    using namespace std;

    Cell& Cell::operator=(int number)
    {
        this->number = number;
        return *this;
    }

    bool Cell::operator==(const Cell& other) const
    {
        return pos == other.pos;
    }

    bool Cell::operator!=(const Cell& other) const
    {
        return !(*this == other);
    }

    bool Cell::operator<(const Cell& other) const
    {
        return pos < other.pos;
    }

    bool Cell::operator<=(const Cell& other) const
    {
        return *this < other || *this == other;
    }

    bool Cell::operator>(const Cell& other) const
    {
        return !(*this <= other);
    }

    bool Cell::operator>=(const Cell& other) const
    {
        return !(*this < other);
    }

    const Position& Cell::position() const
    {
        return pos;
    }

    bool Cell::operator==(const Position& other) const
    {
        return pos == other;
    }

    bool Cell::operator!=(const Position& other) const
    {
        return !(*this == other);
    }

    bool Cell::operator<(const Position& other) const
    {
        return pos < other;
    }

    bool Cell::operator<=(const Position& other) const
    {
        return pos < other || pos == other;
    }

    bool Cell::operator>(const Position& other) const
    {
        return !(pos <= other);
    }

    bool Cell::operator>=(const Position& other) const
    {
        return !(pos < other);
    }

    Cell Cell::with(int number) const
    {
        Cell cell { *this };
        cell.number = number;
        return cell;
    }

    // Cell Predicates

    bool Cell::isEmpty(const Cell& cell)
    {
        return !cell;
    }

    bool Cell::hasNumber(const Cell& cell)
    {
        return !!cell;
    }

    std::set<int> numbersInCells(const Cells& cells)
    {
        return setOp::transform<Cell, int>(cells, [](const Cell& cell) {
            return cell.number;
        });
    }

};
