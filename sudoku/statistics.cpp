//
// Created by Basuke Suzuki on 5/26/18.
//

#include "statistics.h"

namespace sudoku {

    Statistics::Statistics(const Board &board)
    {
        emptyCount = board.availableCells().size();

        valid = board.isValid();
        filled = emptyCount == 0;
        solved = filled && valid;
    }

}