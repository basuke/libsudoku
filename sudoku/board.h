//
// Created by Basuke Suzuki on 5/22/18.
//

#pragma once

#include "cell.h"
#include "region.h"
#include <array>
#include <vector>

namespace sudoku {

    using std::vector;

    class Board {
    public:
        Board();

        Board(const Board& other) = default;
        Board& operator=(const Board& other) = default;

        explicit Board(const std::array<int, 9 * 9>& numbers);
        explicit Board(Cells&& cells);

        const Cell& cell(int x, int y) const;

        const BoundRow& row(int y) const;
        const BoundColumn& column(int x) const;
        const BoundBox& box(int x, int y) const;

        bool isValid() const;
        Cells availableCells() const;
        Cells filledCells() const;

        Board put(Cell step) const;

        Cells cells;
        vector<BoundRow> rows;
        vector<BoundColumn> columns;
        vector<BoundBox> boxes;

    private:
        static int cellIndex(int x, int y);
        static int boxIndex(int x, int y);

        void build();
        const Cell& cellAt(const Position& position) const;
        Cells collectCells(const std::vector<Position>& positions) const;
    };

};

