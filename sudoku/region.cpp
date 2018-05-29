//
// Created by Basuke Suzuki on 5/21/18.
//

#include "region.h"
#include "utils.h"
#include "operations.h"
#include "board.h"

namespace sudoku {

    const Cell& Region::cell(int n) const
    {
        auto temp = setToVector(cells);
        return temp[n - 1];
    }

    bool Region::isValid() const {
        return filledCells().size() == numbers().size();
    }

    bool Region::contain(const Cell& cell) const
    {
        return setOp::contain(cells, cell);
    }

    bool Region::contain(const int number) const
    {
        return setOp::contain(numbers(), number);
    }

    Cells Region::overlap(const Cells &cells) const
    {
        return setOp::overlap(this->cells, cells);
    }

    set<int> Region::numbers() const
    {
        return numbersInCells(filledCells());
    }

    set<int> Region::availableNumbers() const
    {
        return setOp::subtract(allNumbers(), numbers());
    }

    Cells Region::availableCells() const
    {
        return setOp::filter<Cell>(cells, Cell::isEmpty);
    }

    Cells Region::filledCells() const
    {
        return setOp::filter<Cell>(cells, Cell::hasNumber);
    }

    BoundRow::BoundRow(const Board* board, int y, Cells&&cells)
            : Row(y, std::move(cells))
            , WithBoard(board)
    {
    }

    BoundColumn::BoundColumn(const Board* board, int x, Cells&&cells)
            : Column(x, std::move(cells))
            , WithBoard(board)
    {
    }

    BoundBox::BoundBox(const Board* board, int x, int y, Cells&&cells)
            : Box(x, y, std::move(cells))
            , WithBoard(board)
    {
    }

    vector<BoundRow> BoundBox::rows() const
    {
        vector<BoundRow> result;
        for (const auto& row : board->rows) {
            if (!row.overlap(cells).empty())
                result.emplace_back(row);
        }
//        auto ys = setOp::transform<Cell, int>(cells, [](const Cell& cell) {
//            return cell.y();
//        });
//
//        set<BoundRow> result = setOp::transform(ys, [board = this->board](const int& y) {
//            return board->row(y);
//        });

        return result;
    }

    vector<BoundColumn> BoundBox::columns() const
    {
        vector<BoundColumn> result;
        return result;

//        auto xs = setOp::transform<Cell, int>(cells, [](const Cell& cell) {
//            return cell.x();
//        });
//
//        return setOp::transform(xs, [board = this->board](const int& x) {
//            return board->column(x);
//        });
    }

    set<int> allNumbers()
    {
        return { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    }
}