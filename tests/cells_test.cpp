#include "../sudoku/cell.h"
#include "../sudoku/operations.h"
#include "acutest.h"

using namespace std;
using namespace sudoku;

void test_basic() {
    Cell cell1{1, 1}, cell2{2, 1}, cell3{3, 1};
    Cells cells { cell1, cell2, cell3 };

    TEST_CHECK(cells.size() == 3);

    TEST_CHECK(setOp::contain(cells, cell2));
    TEST_CHECK(!setOp::contain(cells, Cell{3, 3}));

    // Test copy constructor
    Cells result2{cells};
    TEST_CHECK(cells == result2);
}

void test_operators()
{
    Cells cells { {1, 1, 5}, {2, 1}, {3, 1}};

    // Test add
    Cells result = setOp::merged(cells, cells);
    TEST_CHECK(cells == result);

    result = setOp::merged(cells, {Cell { 3, 3}});
    TEST_CHECK(result.size() == 4);
    TEST_CHECK(setOp::contain(result, Cell { 3, 3}));

    // Test subtract
    result = setOp::difference(cells, {Cell {3, 3}});
    TEST_CHECK(result.size() == 3);
    TEST_CHECK(cells == result);

    result = setOp::difference(result, cells);
    TEST_CHECK(result.empty());
}

TEST_LIST = {
        { "Cells basic", test_basic},
        { "Cells operation", test_operators },
        { 0 }
};
