#include <iostream>
#include "sudoku/sudoku.h"
#include "sudoku/parser.h"
#include "sudoku/output.h"

using std::vector;

bool isTimingForSeparator(int index)
{
    return (index < 9 && (index % 3) == 0);
}

namespace sudoku {
    struct Statistics {
        size_t emptyCount { };
        bool filled { false };
        bool valid { true };
        bool solved { true };

        explicit Statistics(const Board& board) {
            auto cells = emptyCells(board);
            emptyCount = cells.size();

            valid = isValid(board);
            filled = emptyCount == 0;
            solved = filled && valid;
        }
    };

    class Game {
    public:
        explicit Game(Board&& board) : initialBoard(std::move(board)), statistics(Statistics { board }) { };

        Statistics statistics;
        std::vector<Cell> steps;

        Board currentBoard() const {
            Board board { initialBoard };
            for (const auto& step : steps)
                board = board.put(step);
            return board;
        }

        auto put(Cell step) -> vector<Cell>::iterator {
            auto board = currentBoard().put(step);
            statistics = Statistics { board };
            steps.emplace_back(step);
            return steps.end() - 1;
        };

        void rollback(vector<Cell>::iterator step) {
            steps.erase(step, steps.end());
            statistics = Statistics { currentBoard() };
        }

    protected:
        Board initialBoard;
    };

    using StepFinder = std::function<optional<Cell>(const Board&, const Statistics&)>;

    optional<Cell>find(const Game& game, const vector<StepFinder>& stepFinders);
    Game solve(Board board, vector<StepFinder>&& stepFinders);

    optional<Cell> idiot(const Board& board, const Statistics& statistics) {
        auto cells = emptyCells(board);
        assert(!cells.empty());

        auto cell = *cells.begin();
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

int main() {
    auto numbers = *sudoku::parse(sample);
    Board board {numbers};

    std::cout << board << std::endl;
//    auto game = sudoku::solve(board, { sudoku::Finder(), sudoku::idiot });

//    std::cout << game.currentBoard();
    return 0;
}