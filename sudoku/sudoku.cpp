#include "sudoku.h"

namespace sudoku {

    Board::Board(const std::initializer_list<int>& numbers) {
        auto dest = this->numbers.begin();
        auto stop = this->numbers.end();
        auto src = numbers.begin();

        for (auto& number : numbers) {
            if (dest != stop)
                *dest++ = number;
        }
    }

    int Board::Position::index() const {
        return (y - 1) * 9 + (x - 1);
    }

    optional<Cell>find(const Game& game, const vector<StepFinder>& stepFinders) {
        const auto board = game.currentBoard();
        const auto& statistics = game.statistics;

        for (auto& finder : stepFinders) {
            if (auto step = finder(board, statistics))
                return step;
        }
        return nullopt;
    }

    Game solve(Board board, vector<StepFinder>&& stepFinders) {
        Game game {board};

        while (game.statistics.valid && !game.statistics.solved) {
            if (auto step = find(game, stepFinders))
                game.put(*step);
            else
                break;
        }

        return game;
    }

}