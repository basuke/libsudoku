//
// Created by Basuke Suzuki on 5/21/18.
//

#pragma once

#include "cell.h"

namespace sudoku {

    class Region {
    public:
        Cells cells;

        const Cell& cell(int n) const;

    protected:
        explicit Region(Cells&& cells) : cells(std::move(cells)) {}
    };

    struct Row : public Region {
        const char* kind() const { return "Row"; };

        int y;

        Row(int y, Cells&& cells) : Region(std::move(cells)), y(y) {}
    };

    struct Column : public Region {
        const char* kind() const { return "Column"; };

        int x;

        Column (int x, Cells&& cells) : Region(std::move(cells)), x(x) {}
    };

    struct Box : public Region {
        const char* kind() const { return "Box"; };

        int x;
        int y;

        Box(int x, int y, Cells&& cells) : Region(std::move(cells)), x(x), y(y) {}
    };

    template<typename T>
    bool contain(const T& region, const Cell& cell)
    {
        return contain(region.cells, cell);
    }

    template<typename T1, typename T2>
    Cells subtract(const T1& a, const T2& b)
    {
        return subtract(a.cells, b.cells);
    }

    template<typename T>
    Cells emptyCells(T region)
    {
        return filter(region.cells, isEmpty);
    }

    template<typename T>
    Cells numberCells(T region)
    {
        return filter(region.cells, hasNumber);
    }

    template<typename T>
    bool isValid(T region)
    {
        const auto& cells = numberCells(region);
        std::set<int> numbers;

        for (const auto& cell : cells)
            numbers.insert(cell.number);

        return cells.size() == numbers.size();
    }

}
