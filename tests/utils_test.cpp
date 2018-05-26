#include "../sudoku/utils.h"
#include "../sudoku/cell.h"
#include "acutest.h"

using namespace std;
using namespace sudoku;

void test_conversion()
{
    Cells cells { {1, 1, 5}, {2, 1}, {3, 1}};

    auto result = setToVector(cells);
    TEST_CHECK(result[0].number == 5);
    TEST_CHECK(result.size() == 3);

    auto result2 = vectorToSet(result);
    TEST_CHECK(result2 == cells);
    TEST_CHECK(result2.size() == 3);
}

void test_range()
{
    auto result = range(10, 20);
    TEST_CHECK(result[0] == 10);
    TEST_CHECK(result[10] == 20);
    TEST_CHECK(result.size() == (20 - 10 + 1));

    auto result2 = range(10, 20, 3);
    TEST_CHECK(result2[0] == 10);
    TEST_CHECK(result2[3] == 19);
    TEST_CHECK(result2.size() == 4);

    auto result3 = range(5, 1);
    TEST_CHECK(result3.size() == 5);
    TEST_CHECK(result3[0] == 5);
    TEST_CHECK(result3[4] == 1);

}

TEST_LIST = {
        { "vector / set conversion", test_conversion },
        { "integer ranges", test_range},
        { 0 }
};
