#include <iostream>
#include "sudoku/sudoku.h"
#include "sudoku/parser.h"
#include "sudoku/game.h"
#include "sudoku/output.h"

using std::vector;
using std::cout;
using std::endl;

namespace sudoku {

};

const char* easy1 = R"(
. 6 . | 1 . 2 | . 3 .
7 . 8 | . 6 . | 9 . 2
. 1 . | 9 . 8 | . 7 .
------+-------+------
2 . 6 | . 4 . | 1 . 3
. 9 . | 6 . 7 | . 8 .
1 . 4 | . 9 . | 7 . 5
------+-------+------
. 2 . | 5 . 1 | . 4 .
9 . 5 | . 3 . | 8 . 1
. 3 . | 4 . 9 | . 5 .
)";

const char* hard = R"(
. . . | . 6 . | 2 . .
. . 4 | . . 5 | . 6 .
. 7 . | 4 . . | . . .
------+-------+------
. . 8 | . . 3 | . . 9
. 6 . | . 9 . | . 2 .
4 . . | 7 . . | 5 . .
------+-------+------
. . . | . . 7 | . 3 .
. 2 . | 6 . . | 1 . .
. . 6 | . 8 . | . . .
)";

const char* sample = R"(
2 1 4 | 6 9 3 | 7 5 8
9 5 7 | 2 1 8 | 3 6 4
6 3 8 | 5 7 4 | 2 9 1
------+-------+------
4 6 3 | 9 8 5 | 1 2 7
1 7 9 | 4 6 2 | 8 3 5
8 2 5 | 7 3 1 | 6 4 9
------+-------+------
5 8 6 | 1 2 9 | 4 7 3
7 4 1 | 3 5 6 | 9 8 2
3 9 2 | 8 4 7 | 5 1 6
)";

struct LastNumberInRegion {
    auto operator()(const Board& board, const Statistics& statistics) -> optional<Cell> {
        for (const auto& box : board.boxes) {
            if (auto step = lastNumberInRegion(box))
                return step;
        }

        for (const auto& row : board.rows) {
            if (auto step = lastNumberInRegion(row))
                return step;
        }

        for (const auto& column : board.columns) {
            if (auto step = lastNumberInRegion(column))
                return step;
        }

        return nullopt;
    }

    optional<Cell> lastNumberInRegion(const Region& region) {
        auto cells = region.availableCells();
        auto numbers = region.availableNumbers();

        if (cells.size() == 1 && numbers.size() == 1)
            return (*cells.begin()).with(*numbers.begin());

        return nullopt;
    }

};

struct CellInBoxScreenedByRowsAndColumns {
    auto operator()(const Board& board, const Statistics& statistics) -> optional<Cell> {
        for (auto number : allNumbers()) {
            for (const auto &box : board.boxes) {
                if (!box.contain(number)) {
                    if (auto cell = find(box, number))
                        return cell;
                }
            }
        }
        return nullopt;
    }

    optional<Cell> find(const BoundBox& box, int number)
    {
        auto cells = box.availableCells();

        for (const auto& row : box.rows()) {
            if (row.contain(number))
                setOp::subtract(cells, row.cells);
        }

//        for (auto row : box.columns()) {
//            cells = setOp::subtract(cells, row.cells);
//        }

        if (cells.size() != 1)
            return nullopt;

        auto step = *(cells.begin());
        step.number = number;
        return step;
    }
};

optional<Cell> finderFunc(const Board& board, const Statistics& statistics) {
    return nullopt;
}

struct FinderClass {
    auto operator()(const Board& board, const Statistics& statistics) -> optional<Cell> {
        return nullopt;
    }
};

int main() {
    auto numbers = *sudoku::parse(easy1);
    Board board {numbers};

    Game game {board};

    std::cout << board << std::endl;
    auto game2 = sudoku::solve(board, {
        FinderClass(),
        LastNumberInRegion(),
        CellInBoxScreenedByRowsAndColumns(),
    });

    std::cout << game2.currentBoard();
    return 0;
}