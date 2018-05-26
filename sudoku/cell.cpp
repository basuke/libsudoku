//
// Created by Basuke Suzuki on 5/21/18.
//

#include "cell.h"

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

    bool contain(const Cells& cells, const Cell& cell)
    {
        return cells.find(cell) != cells.end();
    }

    Cells add(const Cells& cells, const Cell& cell)
    {
        Cells result { cells };
        result.insert(cell);
        return result;
    }

    Cells add(const Cells& cells, const Cells& other)
    {
        Cells result { cells };
        for (const auto& cell : other) {
            result.insert(cell);
        }
        return result;
    }

    Cells subtract(const Cells& cells, const Cell& cell)
    {
        Cells result { cells };
        result.erase(cell);
        return result;
    }

    Cells subtract(const Cells& cells, const Cells& other)
    {
        Cells result { cells };
        for (const auto& cell : other) {
            result.erase(cell);
        }
        return result;
    }

    Cells cross(const Cells& a, const Cells& b)
    {
        return filter(a, [&b](const Cell& cell) {
            return contain(b, cell);
        });
    }

    Cells filter(const Cells& cells, std::function<bool(const Cell&)>&& predicate)
    {
        Cells result;
        for (const auto& cell : cells) {
            if (predicate(cell))
                result.insert(cell);
        }
        return result;
    }

    // Cell Predicates

    bool isEmpty(const Cell& cell)
    {
        return !cell;
    }

    bool hasNumber(const Cell& cell)
    {
        return !!cell;
    }
};
