//
// Created by Basuke Suzuki on 5/26/18.
//

#include "game.h"

namespace sudoku {

    Game::Game(const Board& board)
            : initialBoard(board)
            , statistics(Statistics { board })
    {
    }

    Board Game::currentBoard() const
    {
        Board board { initialBoard };
        for (const auto& step : steps)
            board = board.put(step);
        return board;
    }

    auto Game::put(Cell step) -> vector<Cell>::iterator
    {
        auto board = currentBoard().put(step);
        statistics = Statistics { board };
        steps.emplace_back(step);
        return steps.end() - 1;
    };

    void Game::rollback(vector<Cell>::iterator step)
    {
        steps.erase(step, steps.end());
        statistics = Statistics { currentBoard() };
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