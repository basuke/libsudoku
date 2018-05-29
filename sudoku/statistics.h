//
// Created by Basuke Suzuki on 5/26/18.
//

#pragma once

#include "board.h"

namespace sudoku {

    struct Statistics {
        size_t emptyCount {};
        bool filled {false};
        bool valid {true};
        bool solved {true};

        explicit Statistics(const Board &board);
    };

}
