#include <iostream>
#include "sudoku/sudoku.h"
#include "sudoku/parser.h"
#include "sudoku/output.h"

#include <boost/lambda/lambda.hpp>

bool isTimingForSeparator(int index)
{
    return (index < 9 && (index % 3) == 0);
}

namespace sudoku {
    optional<Cell> idiot(const Board& board, const Statistics& statistics) {
        auto emptyCells = board.cells(Cell::isEmpty);
        assert(!emptyCells.empty());

        auto cell = emptyCells[0];
        cell.number = (rand() % 9) + 1;
        return cell;
    }

    struct Finder {
        auto operator()(const Board& board, const Statistics& statistics) -> optional<Cell> {
            return nullopt;
        }
    };
};

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

auto test1() -> decltype(auto) {
    auto board = *sudoku::parse(sample);

    board = board.erase(board.cells());

    return board;
}

int main() {
    Position pos1 { 1, 5 }, pos2 {2, 5};
    Cell cell1 {pos1 }, cell2 { pos2, 2 };

    std::cout << pos1 << " ~ " << pos2 << std::endl;
    std::cout << vector<Position> { pos1, pos2 } << std::endl;

    std::cout << cell1 << " ~ " << cell2 << std::endl;
    Cells cells;
    cells.emplace_back(cell1);
    cells.emplace_back(cell2);
    std::cout << cells << std::endl;

    auto board = test1();

    auto row = board.row(1);
    auto column = board.column(2);
    auto box = board.box({2, 2});

    std::cout << row << std::endl;
    std::cout << column << std::endl;
    std::cout << box << std::endl;
    
    auto result = row - column;
    std::cout << result << std::endl;

    // std::cout << board;

    return 0;
    auto game = sudoku::solve(board, { sudoku::Finder(), sudoku::idiot });

    std::cout << game.currentBoard();
    return 0;
}