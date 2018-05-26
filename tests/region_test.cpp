#include "../sudoku/region.h"
#include "acutest.h"

using namespace std;
using namespace sudoku;

void test_basic()
{
    Row row1 {1, {{1, 1, 1}, {2, 1, 5}, {3, 1}}};

    TEST_CHECK(row1.y == 1);
    TEST_CHECK(contain(row1, {3,1}));

    Row row2 = row1;
    TEST_CHECK(row2.y == 1);
    TEST_CHECK(contain(row2, {3,1}));

    Column col1 {2, {{2, 1, 5}, {2, 2}, {2, 3, 9}}};

    auto result = subtract(row1, col1);
    TEST_CHECK(result.size() == 2);
    TEST_CHECK(contain(result, Cell {1, 1, 1}));
    TEST_CHECK(contain(result, Cell {3, 1}));

    auto e = emptyCells(col1);
    auto n = numberCells(col1);
    TEST_CHECK(e.size() == 1);
    TEST_CHECK(n.size() == 2);
    TEST_CHECK(add(e, n) == col1.cells);
}

void test_isValid()
{
    Column col1 { 2, { {2, 1, 5}, {2, 2}, { 2, 3, 9}}};

    TEST_CHECK(isValid(col1));
}

TEST_LIST = {
        { "basic", test_basic },
        { "isValid", test_isValid},
        { 0 }
};
