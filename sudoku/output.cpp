#include "output.h"
#include "stringify.h"
#include <iostream>

ostream& operator<<(ostream& os, const Position& position)
{
    os << stringify(position);
    return os;
}

ostream& operator<<(ostream& os, const vector<Position>& positions)
{
    os << stringify(positions);
    return os;
}

ostream& operator<<(ostream& os, const Cell& cell)
{
    os << stringify(cell);
    return os;
}

ostream& operator<<(ostream& os, const Cells& cells)
{
    os << stringify(cells);
    return os;
}

ostream& operator<<(ostream& os, const Row& row)
{
    os << stringify(row);
    return os;
}

ostream& operator<<(ostream& os, const Column& column)
{
    os << stringify(column);
    return os;
}

ostream& operator<<(ostream& os, const Box& box)
{
    os << stringify(box);
    return os;
}

ostream& operator<<(ostream& os, const Board& board)
{
    os << stringify(board);
    return os;
}

