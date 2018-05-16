#pragma once

#include "sudoku.h"
#include <string>
#include <vector>

namespace sudoku {
    std::string stringify(const Position& position);
    std::string stringify(const std::vector<Position>& positions);
    std::string stringify(const Cell& cell);
    std::string stringify(const Cells& cells);
    std::string stringify(const Row& row);
    std::string stringify(const Column& column);
    std::string stringify(const Box& box);
    std::string stringify(const Board& board);
}

