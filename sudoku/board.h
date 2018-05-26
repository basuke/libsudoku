//
// Created by Basuke Suzuki on 5/22/18.
//

#pragma once

#include "cell.h"
#include "region.h"
#include <array>
#include <vector>

namespace sudoku {

    class Board {
    public:
        Board();

        Board(const Board& other) = default;
        Board& operator=(const Board& other) = default;

        explicit Board(const std::array<int, 9 * 9>& numbers);
        explicit Board(Cells&& cells);

//        template <typename Container, typename T>
//        explicit Board(const Container<T>& numbers) : Board() {
//            auto dest = cells.begin();
//            auto stop = cells.end();
//
//            for (auto &number : numbers) {
//                if (dest == stop)
//                    break;
//
//                (*dest++).number = number;
//            }
//
//            build();
//        }
//
//        explicit Board(const std::initializer_list<int>& numbers);
//
        const Cell& cell(int x, int y) const;

        const Row& row(int y) const;
        const Column& column(int x) const;
        const Box& box(int x, int y) const;

        Board put(Cell step) const;

        Cells cells;
        std::vector<Row> rows;
        std::vector<Column> columns;
        std::vector<Box> boxes;

    private:
        static int cellIndex(int x, int y);
        static int boxIndex(int x, int y);

        void build();
        const Cell& cellAt(const Position& position) const;
        Cells collectCells(const std::vector<Position>& positions) const;
    };

};

