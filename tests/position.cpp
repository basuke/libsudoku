#include "../sudoku/position.h"
#include "acutest.h"
#include <set>
#include <array>

using namespace std;
using namespace sudoku;

void test_basic()
{
    Position pos1 {  3, 1 };
    Position pos2 { pos1 };
    Position pos3 { 4, 2 };
    Position pos4 { 1, 3 };

    array<Position, 4> ts = {pos1, pos2, pos3, pos4};

    TEST_CHECK(ts[0].x == 3);
    TEST_CHECK(ts[0].y == 1);

    // Copy constructor

    TEST_CHECK(ts[1].x == 3);
    TEST_CHECK(ts[1].y == 1);

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
}

void test_set()
{
    Position pos1 { 1, 2 }, pos2 { 2, 2 }, pos3 { 3, 1 };
    array<Position, 3> ts {pos1, pos2, pos3};

    set<Position> result;

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

TEST_LIST = {
        { "basic", test_basic },
        { "set of position", test_set },
        { 0 }
};
