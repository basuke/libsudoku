//
// Created by Basuke Suzuki on 5/21/18.
//

#pragma once

#include "cell.h"
#include "operations.h"

namespace sudoku {

    using std::vector;

    class Board;
    
    class Region {
    public:
        Cells cells;

        const Cell& cell(int n) const;

        bool isValid() const;
        bool contain(const Cell& cell) const;
        bool contain(int number) const;
        Cells overlap(const Cells &cells) const;

        set<int> numbers() const;
        set<int> availableNumbers() const;

        Cells availableCells() const;
        Cells filledCells() const;

    protected:
        explicit Region(Cells&& cells) : cells(move(cells)) {}
    };

    class WithBoard {
    public:
        explicit WithBoard(const Board* board) : board { board } {}

        WithBoard(const WithBoard&) = default;
        WithBoard& operator=(const WithBoard& other) = default;
        
    protected:
        const Board* board;
    };
    
    struct Row : public Region {
        const char* kind() const { return "Row"; };

        int y;

        Row(int y, Cells&& cells) : Region(move(cells)), y(y) {}
    };

    struct Column : public Region {
        const char* kind() const { return "Column"; };

        int x;

        Column (int x, Cells&& cells) : Region(move(cells)), x(x) {}
    };

    struct Box : public Region {
        const char* kind() const { return "Box"; };

        int x;
        int y;

        Box(int x, int y, Cells&& cells) : Region(move(cells)), x(x), y(y) {}
    };

    struct BoundRow : public Row, public WithBoard {
        BoundRow(const Board* board, int y, Cells&&cells);
    };

    struct BoundColumn : public Column, public WithBoard {
        BoundColumn(const Board* board, int x, Cells&&cells);
    };

    struct BoundBox : public Box, public WithBoard {
        BoundBox(const Board* board, int x, int y, Cells&&cells);

        vector<BoundRow> rows() const;
        vector<BoundColumn> columns() const;
    };

    set<int> allNumbers();
}
