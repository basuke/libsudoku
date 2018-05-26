#pragma once

#include "position.h"
#include "cell.h"
#include "region.h"
#include "board.h"
#include <set>
#include <ostream>

using namespace sudoku;
using std::set;
using std::ostream;

ostream& operator<<(ostream& os, const Position& position);
ostream& operator<<(ostream& os, const set<Position>& positions);
ostream& operator<<(ostream& os, const Cell& cell);
ostream& operator<<(ostream& os, const Cells& cells);
ostream& operator<<(ostream& os, const Row& cell);
ostream& operator<<(ostream& os, const Column& cell);
ostream& operator<<(ostream& os, const Box& cell);
ostream& operator<<(ostream& os, const Board& cell);
