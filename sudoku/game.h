//
// Created by Basuke Suzuki on 5/26/18.
//

#pragma once

#include "board.h"
#include "statistics.h"
#include <vector>
#include <experimental/optional>

namespace sudoku {

    using std::vector;
    using std::experimental::optional;
    using std::experimental::nullopt;

    class Game {
    public:
        explicit Game(const Board& board);

        Statistics statistics;
        vector<Cell> steps;

        Board currentBoard() const;

        auto put(Cell step) -> vector<Cell>::iterator;
        void rollback(vector<Cell>::iterator step);

    protected:
        Board initialBoard;
    };

    using StepFinder = std::function<optional<Cell>(const Board&, const Statistics&)>;

    optional<Cell>find(const Game& game, const vector<StepFinder>& stepFinders);
    Game solve(Board board, vector<StepFinder>&& stepFinders);

}
