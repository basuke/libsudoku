#pragma once

#include <experimental/optional>
#include <array>
#include <set>
#include <vector>

namespace sudoku {

    using std::experimental::optional;
    using std::experimental::nullopt;
    using std::function;
    using std::vector;
    using std::array;
    using std::set;
    using Number = int;

    class Board {
    public:
        Board() = default;

        Board(const std::initializer_list<int>& numbers);

        template<typename T>
        explicit Board(const array<T, 9 * 9>& numbers) {
            std::copy(numbers.begin(), numbers.end(), this->numbers.begin());
        }

        struct Position {
            int x, y;

            bool operator==(const Position& other) {
                return x == other.x && y == other.y;
            }

            bool operator!=(const Position& other) {
                return !(*this == other);
            }

            int index() const;
        };

        /**
         * Cell
         */
        struct Cell : public Position {
            explicit Cell(Position position) : Position(position) {}
            Cell(Position position, Number number) : number(number), Position(position) {}

            Number number { 0 };

            bool operator==(const Cell& other) const {
                return x == other.x && y == other.y;
            }

            bool operator!=(const Cell& other) const {
                return !(*this == other);
            }

            bool operator==(Number number) const {
                return this->number == number;
            }

            bool operator!=(Number number) const {
                return this->number != number;
            }

            Position position() const {
                return { x, y };
            }

            using Predicate = std::function<bool(const Cell&)>;

            static bool isNotEmpty(const Cell& cell) {
                return cell.number != 0;
            }

            static bool isEmpty(const Cell& cell) {
                return !isNotEmpty(cell);
            }

            static auto has(Number n) -> Predicate {
                return [n] (const Cell& cell) {
                    return cell.number == n;
                };
            }
        };

        /**
         * Cells
         */
        class Cells : public vector<Cell> {
        public:
            Cells() = default;
            Cells(const Cells&) = default;
            Cells(Cells&&) = default;

            Cells& operator=(const Cells&) = default;
            Cells& operator=(Cells&&) = default;

            long count(Cell::Predicate&& predicate) const {
                return std::count_if(begin(), end(), move(predicate));
            }

            operator vector<Position>&&() { return positions(); }

            vector<Position>&& positions() const {
                vector<Position> result;

                std::transform(begin(), end(), std::back_inserter(result), [](const auto& cell) {
                    return cell.position();
                });
                // auto p = result.begin();
                // for (const auto& cell : *this)
                //     *p++ = cell.position();

                return std::move(result);
            }

            bool contains(const Cell& needle) const {
                return std::any_of(begin(), end(), [&needle](const Cell& cell) {
                    return cell == needle;
                });
            }
            Cells&& add(const Cell& cell) const {
                Cells result = *this;
                if (!contains(cell))
                    result.emplace_back(cell);
                return std::move(result);
            }

            Cells&& add(const Cells& other) const {
                auto result = *this;
                std::copy_if(other.begin(), other.end(), back_inserter(result), [this](const auto& cell) {
                    return !contains(cell);
                });
                return std::move(result);
            }

            Cells&& subtract(const Cell& cell) const {
                Cells result;
                std::copy_if(begin(), end(), back_inserter(result), [&cell](const auto& a) {
                    return a != cell;
                });
                return std::move(result);
            }

            Cells&& subtract(const Cells& other) const {
                auto result = *this;
                std::copy_if(begin(), end(), back_inserter(result), [&other](const auto& a) {
                    return !other.contains(a);
                });
                return std::move(result);
            }

            Cells&& operator+(const Cell& cell) const { return add(cell); }
            Cells&& operator-(const Cell& cell) const { return subtract(cell); }

            Cells&& operator+(const Cells& other) const { return add(other); }
            Cells&& operator-(const Cells& other) const { return subtract(other); }

            Cells&& filter(Cell::Predicate && predicate) const {
                Cells result;
                std::copy_if(begin(), end(), std::back_inserter(result), std::move(predicate));
                return std::move(result);
            }

            bool isValid() const {
                auto numbers = uniqueNumbers();
                auto c = count(Cell::isNotEmpty);
                return numbers.size() == c;
            }

            vector<Number> uniqueNumbers() const {
                vector<Number> numbers;
                std::transform(begin(), end(), std::back_inserter(numbers), [] (const auto& c) {
                    return c.number;
                });

                vector<Number> result;
                std::copy_if(numbers.begin(), numbers.end(), std::back_inserter(result), [] (auto n) { return n; });
                std::sort(result.begin(), result.end());
                auto last = std::unique(result.begin(), result.end());
                result.erase(last, result.end());
                result.shrink_to_fit();
                return result;
            }
        };

        /**
         * Row
         */
        class Row : public Cells {
        public:
            constexpr const char* kind() const { return "Row"; }
            bool isBorderTiming(const Cell& cell) const {
                return (cell.x % 3) == 0;
            }

            explicit Row(int y) : Cells(), y(y) { }
            int y;
        };

        /**
         * Column
         */
        class Column : public Cells {
        public:
            constexpr const char* kind() const { return "Column"; }
            bool isBorderTiming(const Cell& cell) const {
                return (cell.y % 3) == 0;
            }

            explicit Column(int x) : Cells(), x(x) { }
            int x;
        };

        /**
         * Box
         */
        class Box : public Cells {
        public:
            constexpr const char* kind() const { return "Box"; }
            bool isBorderTiming(const Cell& cell) const {
                return (cell.x % 3) == 0;
            }

            Box(int x, int y) : Cells(), x(x), y(y) { }
            int x;
            int y;
        };

        Cell cell(Position position) const {
            return Cell(position, numbers[position.index()]);
        }

        Row row(int y) const {
            Row row { y };
            for (int x = 1; x <= 9; ++x)
                row.emplace_back(cell({x, y}));
            return row;
        }

        Column column(int x) const {
            Column column { x };
            for (int y = 1; y <= 9; ++y)
                column.emplace_back(cell({x, y}));
            return column;
        }

        Position boxTopLeftPosition(Position boxPosition) const {
            return {
                    (boxPosition.x - 1) * 3 + 1,
                    (boxPosition.y - 1) * 3 + 1
            };
        }

        Box box(Position position) const {
            Box box { position.x, position.y };
            auto [left, top] = boxTopLeftPosition(position);
            auto [right, bottom] = Position { left + 2, top + 2 };

            for (int y = top; y <= bottom; ++y)
                for (int x = left; x <= right; ++x)
                    box.emplace_back(cell({x, y}));
            return box;
        }

        vector<Position> positions() const {
            vector<Position> result;

            for (int y = 1; y <= 9; ++y) {
                for (int x = 1; x <= 9; ++x) {
                    result.emplace_back(Position {x, y});
                }
            }

            return result;
        };

        unsigned count(Cell::Predicate&& predicate) const {
            unsigned count = 0;
            for (const auto& position : positions()) {
                auto c = cell(position);

                if (predicate(c))
                    ++count;
            }
            return count;
        }

        Cells cells() const {
            Cells cells { };
            for (const auto& position : positions())
                cells.emplace_back(cell(position));
            return cells;
        }

        Cells cells(Cell::Predicate&& predicate) const {
            Cells cells { };
            for (const auto& position : positions()) {
                auto c = cell(position);

                if (predicate(c))
                    cells.emplace_back(c);
            }
            return cells;
        }

        vector<Row> rows() const {
            vector<Row> rows;
            for (int y = 1; y <= 9; ++y)
                rows.emplace_back(row(y));
            return rows;
        }

        vector<Column> columns() const {
            vector<Column> columns;
            for (int x = 1; x <= 9; ++x)
                columns.emplace_back(column(x));
            return columns;
        }

        vector<Box> boxes() const {
            vector<Box> boxes;
            for (int y = 1; y <= 3; ++y)
                for (int x = 1; x <= 3; ++x)
                    boxes.emplace_back(box({x, y}));
            return boxes;
        }

        Board put(Position position, Number number) const {
            assert(number >= 1 && number <= 9);
            Board board = *this;
            board.numbers[position.index()] = number;
            return board;
        }

        Board erase(Position position) const {
            Board board = *this;
            board.numbers[position.index()] = 0;
            return board;
        }

        Board erase(const vector<Position>& positions) const {
            Board board = *this;
            for (const auto& position : positions)
                board.numbers[position.index()] = 0;
            return board;
        }

        bool isValid() const {
            for (const auto& row : rows()) {
                if (!row.isValid())
                    return false;
            }

            for (const auto& column : columns()) {
                if (!column.isValid())
                    return false;
            }

            for (const auto& box : boxes()) {
                if (!box.isValid())
                    return false;
            }

            return true;
        }

    private:
        array<Number, 9 * 9> numbers { };
    };

    using Position = Board::Position;
    using Cell = Board::Cell;
    using Cells = Board::Cells;
    using Row = Board::Row;
    using Column = Board::Column;
    using Box = Board::Box;

    struct Statistics {
        size_t emptyCount { };
        bool filled { false };
        bool valid { true };
        bool solved { true };

        explicit Statistics(const Board& board) {
            auto emptyCells = board.cells(Cell::isEmpty);
            emptyCount = emptyCells.size();

            valid = board.isValid();
            filled = emptyCount == 0;
            solved = filled && valid;
        }
    };

    class Game {
    public:
        struct StepLog {
            Position position;
            Number number { };
        };

        explicit Game(Board board) : initialBoard(board), statistics(Statistics { board }) { };

        Statistics statistics;
        vector<StepLog> steps;

        Board currentBoard() const {
            Board board { initialBoard };
            for (const auto& step : steps)
                board = board.put(step.position, step.number);
            return board;
        }

        auto put(Position position , Number number) -> vector<StepLog>::iterator {
            StepLog step = { position, number };

            auto board = currentBoard().put(position, number);
            statistics = Statistics { board };
            steps.emplace_back(step);
            return steps.end() - 1;
        };

        auto put(int x, int y, Number number) -> vector<StepLog>::iterator {
            return put({ x, y }, number);
        }

        auto put(Cell cell) -> vector<StepLog>::iterator {
            return put({ cell.x, cell.y }, cell.number);
        }

        void rollback(vector<StepLog>::iterator step) {
            steps.erase(step, steps.end());
            statistics = Statistics { currentBoard() };
        }

    protected:
        Board initialBoard;
    };

    using StepFinder = std::function<optional<Cell>(const Board&, const Statistics&)>;

    optional<Cell>find(const Game& game, const vector<StepFinder>& stepFinders);
    Game solve(Board board, vector<StepFinder>&& stepFinders);
};

