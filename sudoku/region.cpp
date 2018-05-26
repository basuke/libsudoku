//
// Created by Basuke Suzuki on 5/21/18.
//

#include "region.h"
#include "utils.h"

namespace sudoku {

    const Cell& Region::cell(int n) const
    {
        auto temp = setToVector(cells);
        return temp[n - 1];
    }
}