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

TEST_LIST = {
        { "Cell basic", test_basic },
        { "set of cell", test_set },
        { "Position conversion", test_positionConversion },
        { 0 }
};
