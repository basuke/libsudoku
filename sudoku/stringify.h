#pragma once

#include "position.h"
#include "cell.h"
#include "region.h"
#include "board.h"
#include <string>

namespace sudoku {
    using std::string;
    using std::vector;

    string stringify(const Position& position);
    string stringify(const vector<Position>& positions);
    string stringify(const Cell& cell);
    string stringify(const Cells& cells);
    string stringify(const Row& row);
    string stringify(const Column& column);
    string stringify(const Box& box);
    string stringify(const Board& board);
}

