#include "../sudoku/cell.h"
#include "../sudoku/operations.h"
#include "acutest.h"
#include <set>
#include <array>

using namespace std;
using namespace sudoku;
//
// Created by Basuke Suzuki on 5/21/18.
//

void test_basic()
{
    Cell cell1 { 3, 1, 5 };
    Cell cell2 { cell1 };
    Cell cell3 { 4, 2 };
    Cell cell4 { 1, 3 };
    array<Cell, 4> ts = {cell1, cell2, cell3, cell4};

    TEST_CHECK(ts[0].x() == 3);
    TEST_CHECK(ts[0].y() == 1);

    // Copy constructor

    TEST_CHECK(ts[1].x() == 3);
    TEST_CHECK(ts[1].y() == 1);

    // Equal operator

    TEST_CHECK(ts[0] == ts[1]);
    TEST_CHECK(ts[0] != ts[2]);
    TEST_CHECK(!(ts[0] != ts[1]));
    TEST_CHECK(!(ts[0] == ts[2]));

    // Compare operator

    TEST_CHECK(ts[0] == ts[0]);
    TEST_CHECK(ts[0] >= ts[1]);
    TEST_CHECK(ts[0] <= ts[1]);
    TEST_CHECK(ts[0] < ts[2]);
    TEST_CHECK(ts[0] < ts[3]);

    TEST_CHECK(ts[1] == ts[0]);
    TEST_CHECK(ts[1] >= ts[1]);
    TEST_CHECK(ts[1] < ts[2]);
    TEST_CHECK(ts[1] < ts[3]);

    TEST_CHECK(ts[2] > ts[0]);
    TEST_CHECK(ts[2] >= ts[1]);
    TEST_CHECK(ts[2] == ts[2]);
    TEST_CHECK(ts[2] < ts[3]);

    TEST_CHECK(ts[3] > ts[0]);
    TEST_CHECK(ts[3] >= ts[1]);
    TEST_CHECK(ts[3] > ts[2]);
    TEST_CHECK(ts[3] == ts[3]);

    TEST_CHECK(cell1 == 5);
    TEST_CHECK(cell1 != 7);
    TEST_CHECK(!!cell1);
    TEST_CHECK(!!cell2);
    TEST_CHECK(!cell3);
    TEST_CHECK(!cell4);
    TEST_CHECK(cell4 != 7);
}

void test_set()
{
    Cell cell1 { 1, 2 }, cell2 { 2, 2 }, cell3 { 3, 1 };
    array<Cell, 3> ts {cell1, cell2, cell3};

    set<Cell> result;

    result.insert(ts[0]);
    TEST_CHECK(result.size() == 1);

    result.insert(ts[0]);
    TEST_CHECK(result.size() == 1);

    result.insert(ts[1]);
    result.insert(ts[2]);
    TEST_CHECK(result.size() == 3);

    auto found = result.find(ts[2]);
    TEST_CHECK(found != result.end());

}

void test_positionConversion()
{
    Cell cell1 { 1, 2, 5 };
    Position pos1 { 1, 2 };
    TEST_CHECK(cell1.position() == pos1);
}

void test_cells() {
    Cell cell1{1, 1}, cell2{2, 1}, cell3{3, 1};
    Cells cells;

    cells.insert(cell1);
    cells.insert(cell1);
    cells.insert(cell2);
    cells.insert(cell3);
    TEST_CHECK(cells.size() == 3);

    TEST_CHECK(setOp::contain(cells, cell2));
    TEST_CHECK(!setOp::contain(cells, Cell{3, 3}));

    // Test copy constructor
    Cells result2{cells};
    TEST_CHECK(cells == result2);
}

void test_cellsOperation()
{
    Cells cells { {1, 1, 5}, {2, 1}, {3, 1}};

    // Test add
    Cells result = setOp::add(cells, cells);
    TEST_CHECK(cells == result);

    result = setOp::add(cells, Cell { 3, 3});
    TEST_CHECK(result.size() == 4);
    TEST_CHECK(setOp::contain(result, Cell { 3, 3}));

    // Test subtract
    result = setOp::subtract(cells, Cell {3, 3});
    TEST_CHECK(result.size() == 3);
    TEST_CHECK(cells == result);

    result = setOp::subtract(result, cells);
    TEST_CHECK(result.size() == 0);
}

TEST_LIST = {
        { "Cell basic", test_basic },
        { "set of cell", test_set },
        { "Position conversion", test_positionConversion },
        { "Cells basic", test_cells},
        { "Cells operation", test_cellsOperation },
        { 0 }
};
