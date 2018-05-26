#include "../sudoku/parser.h"
#include "../sudoku/board.h"
#include "../sudoku/cell.h"
#include "acutest.h"

using namespace std;
using namespace sudoku;

void test_basic() {
    Cells cells{{1, 1, 5},
                {2, 1},
                {3, 1}};

    Board board;

    TEST_CHECK(board.cell(1, 1).x() == 1);
    TEST_CHECK(board.cell(5, 6).y() == 6);
    TEST_CHECK(board.row(7).y == 7);
    TEST_CHECK(contain(board.row(7), Cell(1, 7)));
    TEST_CHECK(board.column(3).x == 3);
    TEST_CHECK(contain(board.column(3), Cell{3, 5}));
    TEST_CHECK(board.box(3, 3).y == 3);
    TEST_CHECK(contain(board.box(3, 3), Cell{9, 7}));

    TEST_CHECK(board.rows.size() == 9);
    TEST_CHECK(board.columns.size() == 9);
    TEST_CHECK(board.boxes.size() == 9);
}

const char* sampleBoard = R"(
    2 1 4 | 6 9 3 | 7 5 8
    9 5 7 | 2 1 8 | 3 6 4
    6 3 8 | 5 7 4 | 2 9 1
    ------+-------+------
    4 6 3 | 9 8 5 | 1 2 7
    1 7 9 | 4 6 2 | 8 3 5
    8 2 5 | 7 3 1 | 6 4 9
    ------+-------+------
    5 8 6 | 1 2 9 | 4 7 3
    7 4 1 | 3 5 6 | 9 8 2
    3 9 2 | 8 4 7 | 5 1 6)";

void test_basic_with_data()
{
    auto result = parse(sampleBoard);
    TEST_CHECK(!!result);

    Board board { *result };

    TEST_CHECK(board.cell(1, 1) == 2);
    TEST_CHECK(board.cell(2, 2) == 5);
    TEST_CHECK(board.cell(3, 3) == 8);
    TEST_CHECK(board.cell(4, 4) == 9);
    TEST_CHECK(board.cell(5, 5) == 6);
    TEST_CHECK(board.cell(6, 6) == 1);
    TEST_CHECK(board.cell(7, 7) == 4);
    TEST_CHECK(board.cell(8, 8) == 8);
    TEST_CHECK(board.cell(9, 9) == 6);


    TEST_CHECK(board.row(7).cell(5) == 2);
    TEST_CHECK(board.column(3).cell(5) == 9);
    TEST_CHECK(board.box(3, 3).cell(5) == 8);
}

TEST_LIST = {
        { "basic", test_basic },
        { "basic 2", test_basic_with_data },
        { 0 }
};
