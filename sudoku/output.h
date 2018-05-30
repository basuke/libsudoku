#pragma once

#include "position.h"
#include "cell.h"
#include "region.h"
#include "board.h"
#include <ostream>

using namespace sudoku;
using std::vector;
using std::ostream;

ostream& operator<<(ostream& os, const Position& position);
ostream& operator<<(ostream& os, const vector<Position>& positions);
ostream& operator<<(ostream& os, const Cell& cell);
ostream& operator<<(ostream& os, const Cells& cells);
ostream& operator<<(ostream& os, const Row& cell);
ostream& operator<<(ostream& os, const Column& cell);
ostream& operator<<(ostream& os, const Box& cell);
ostream& operator<<(ostream& os, const Board& cell);
