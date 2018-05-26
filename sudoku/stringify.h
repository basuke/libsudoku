#pragma once

#include "position.h"
#include "cell.h"
#include "region.h"
#include "board.h"
#include <string>

namespace sudoku {
    std::string stringify(const Position& position);
    std::string stringify(const std::set<Position>& positions);
    std::string stringify(const Cell& cell);
    std::string stringify(const Cells& cells);
    std::string stringify(const Row& row);
    std::string stringify(const Column& column);
    std::string stringify(const Box& box);
    std::string stringify(const Board& board);
}

