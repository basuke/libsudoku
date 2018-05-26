//
// Created by Basuke Suzuki on 5/22/18.
//

#include "board.h"
#include "utils.h"

namespace sudoku {

    template<typename ITER>
    static auto buildCells(ITER p) -> Cells
    {
        Cells cells;
        for (int y = 1; y <= 9; y++) {
            for (int x = 1; x <= 9; x++) {
                cells.insert(Cell {x, y, *(p++)});
            }
        }
        return cells;
    }

    struct ZeroGenerator {
        int operator*() { return 0; }
        ZeroGenerator& operator++() { return *this; }
        ZeroGenerator operator++(int) { return *this; }
    };

    Board::Board()
            : cells(buildCells(ZeroGenerator {}))
    {
        build();
    }

    Board::Board(const std::array<int, 9 * 9>& numbers)
            : cells(buildCells(numbers.begin()))
    {
        build();
    }

    Board::Board(Cells&& cells)
    {
        cells = std::move(cells);
        build();
    }

//    template <typename Container>
//    Board::Board(const Container<int>& numbers)
//            : Board()
//    {
//        auto dest = cells.begin();
//        auto stop = cells.end();
//
//        for (auto& number : numbers) {
//            if (dest == stop)
//                break;
//
//            (*dest++).number = number;
//        }
//
//        build();
//    }
//
//    Board::Board(const std::initializer_list<int>& numbers)
//        : Board<std::initializer_list>(numbers)
//    {
//    }
//
//    template<typename T>
//    Board::Board(const std::vector<T>& numbers) {
//        auto ptr = numbers.begin();
//        for (int y = 1; y <= 9; y++) {
//            for (int x = 1; x <= 9; x++) {
//                cells.emplace_back({x, y, *ptr++});
//            }
//        }
//        build();
//    }

    int Board::cellIndex(int x, int y)
    {
        assert(x >= 1 && x <= 9);
        assert(y >= 1 && y <= 9);
        return (y - 1) * 9 + (x - 1);
    }

    int Board::boxIndex(int x, int y)
    {
        assert(x >= 1 && x <= 3);
        assert(y >= 1 && y <= 3);
        return (y - 1) * 3 + (x - 1);
    }

    void Board::build()
    {
        rows.clear();
        columns.clear();
        boxes.clear();

        auto r = range(1, 9);

        for (auto y : r) {
            std::vector<Position> positions;
            std::transform(r.begin(), r.end(), back_inserter(positions), [y](int x) {
                return Position {x, y};
            });
            rows.emplace_back(Row {y, collectCells(positions)});
        }

        for (auto x : r) {
            std::vector<Position> positions;
            std::transform(r.begin(), r.end(), back_inserter(positions), [x](int y) {
                return Position {x, y};
            });
            columns.emplace_back(Column {x, collectCells(positions)});
        }

        auto r2 = range(0, 2);

        for (auto y0 : r2) {
            auto startY = y0 * 3;

            for (auto x0 : r2) {
                auto startX = x0 * 3;

                std::vector<Position> positions;

                for (auto y : range(startY + 1, startY + 3)) {
                    for (auto x : range(startX + 1, startX + 3)) {
                        positions.emplace_back(Position {x, y});
                    }
                }

                boxes.emplace_back(Box {x0 + 1, y0 + 1, collectCells(positions)});
            }
        }
    }

    Cells Board::collectCells(const std::vector<Position>& positions) const
    {
        std::vector<Cell> result;

        std::transform(positions.begin(),
                       positions.end(),
                       back_inserter(result),
                       [this](const Position& position) {
                           return cellAt(position);
                       });

        return vectorToSet(result);
    }

    const Cell& Board::cellAt(const Position& position) const
    {
        auto found = cells.find(Cell { position });
        return *found;
    }

    const Cell& Board::cell(int x, int y) const
    {
        return cellAt({x, y});
    }

    const Row& Board::row(int y) const
    {
        assert(y >= 1 && y <= 9);
        return rows[y - 1];
    }

    const Column& Board::column(int x) const
    {
        assert(x >= 1 && x <= 9);
        return columns[x - 1];
    }

    const Box& Board::box(int x, int y) const
    {
        return boxes[boxIndex(x, y)];
    }

    Board Board::put(Cell step) const
    {
        Cells cells = this->cells;
        cells.erase(step);
        cells.insert(step);
        return Board {std::move(cells)};
    }

}