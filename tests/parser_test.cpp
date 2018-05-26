#include "../sudoku/parser.h"
#include "acutest.h"

using namespace std;
using namespace sudoku;

void test_basic()
{
    const char* sample = R"(
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

    auto result = parse(sample);
    TEST_CHECK(!!result);

    auto numbers = *result;

    TEST_CHECK(numbers[0] == 2);
    TEST_CHECK(numbers[10] == 5);
    TEST_CHECK(numbers[20] == 8);
    TEST_CHECK(numbers[30] == 9);
    TEST_CHECK(numbers[40] == 6);
    TEST_CHECK(numbers[50] == 1);
    TEST_CHECK(numbers[60] == 4);
    TEST_CHECK(numbers[70] == 8);
    TEST_CHECK(numbers[80] == 6);
}

TEST_LIST = {
        { "basic", test_basic },
        { 0 }
};
