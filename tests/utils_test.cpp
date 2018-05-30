#include "../sudoku/operations.h"
#include "../sudoku/cell.h"
#include "acutest.h"
#include <iostream>

using namespace std;
using namespace sudoku;

void test_range()
{
    auto result = setOp::range(10, 20);
    TEST_CHECK(result[0] == 10);
    TEST_CHECK(result[10] == 20);
    TEST_CHECK(result.size() == (20 - 10 + 1));

    auto result2 = setOp::range(10, 20, 3);
    TEST_CHECK(result2[0] == 10);
    TEST_CHECK(result2[3] == 19);
    TEST_CHECK(result2.size() == 4);

    auto result3 = setOp::range(5, 1);
    TEST_CHECK(result3.size() == 5);
    TEST_CHECK(result3[0] == 5);
    TEST_CHECK(result3[4] == 1);

}

void test_contain()
{
    auto test = setOp::range(10, 20);
    TEST_CHECK(setOp::contain(test, 10));
    TEST_CHECK(setOp::contain(test, 15));
    TEST_CHECK(setOp::contain(test, 20));

    TEST_CHECK(!setOp::contain(test, 9));
    TEST_CHECK(!setOp::contain(test, 21));
}

void test_forEach()
{
    vector<int> test = setOp::range(1, 10);
    int sum = 0;
    setOp::forEach<int>(test, [&sum](int& item) {
        sum += item;
    });
    TEST_CHECK(sum == 55);
}

void test_filter()
{
    auto test = setOp::range(1, 10);
    auto result = setOp::filter<int>(test, [](auto val) {
        return val % 3 == 0;
    });

    TEST_CHECK(result.size() == 3);
}

void test_map()
{
    auto test = setOp::range(1, 4);
    auto result = setOp::map<int, char>(test, [](int val) {
        return 'a' + val - 1;
    });
    vector<char> expected { 'a', 'b', 'c', 'd'};

    TEST_CHECK(result == expected);
}

void test_add()
{
    auto test = setOp::range(3, 10);
    setOp::add(test, setOp::range(1, 4));

    auto expected = setOp::range(1, 10);
    TEST_CHECK(test == expected);
}

void test_merged()
{
    auto test = setOp::range(1, 4);
    auto result = setOp::merged(test, setOp::range(10, 3));

    auto expected = setOp::range(1, 10);
    TEST_CHECK(result == expected);
}

void test_subtract()
{
    auto test = setOp::range(1, 4);
    setOp::subtract(test, setOp::range(3, 10));

    auto expected = setOp::range(1, 2);
    TEST_CHECK(test == expected);
}

void test_difference()
{
    auto test = setOp::range(1, 5);
    auto result = setOp::difference(test, setOp::range(4, 6));

    auto expected = setOp::range(1, 3);
    TEST_CHECK(result == expected);
}

void test_product()
{
    auto test = setOp::range(1, 4);
    setOp::product(test, setOp::range(3, 10));

    auto expected = setOp::range(3, 4);
    TEST_CHECK(test == expected);
}

void test_overlapped()
{
    auto test = setOp::range(1, 5);
    auto result = setOp::overlapped(test, setOp::range(4, 6));

    TEST_CHECK(result == setOp::range(4, 5));

    result = setOp::overlapped(test, setOp::range(8, 10));
    TEST_CHECK(result.empty());
}

TEST_LIST = {
        { "range", test_range},
        { "contain", test_contain},
        { "forEach", test_forEach},
        { "filter", test_filter},
        { "map", test_map},
        { "add", test_add},
        { "merged", test_merged},
        { "subtract", test_subtract},
        { "difference", test_difference},
        { "product", test_product},
        { "overlapped", test_overlapped},
        { 0 }
};
