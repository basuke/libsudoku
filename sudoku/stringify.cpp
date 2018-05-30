#include "stringify.h"
#include <vector>

namespace sudoku {

    static char numchar(int c)
    {
        if (!c)
            return '.';

        return '0' + static_cast<char>(c);
    }

    template<typename C>
    static string join(const C& items, const string& delimiter)
    {
        using T = typename C::value_type;
        vector<string> itemStrs;

        std::transform(items.begin(), items.end(), std::back_inserter(itemStrs), [](const T& item) {
            return stringify(item);
        });

        string result;
        for (auto p = items.begin(); p != items.end(); ++p) {
            result += (p == items.begin()) ? "[" : ", ";
            result += stringify(*p);
        }
        result += "]";
        return result;
    }

    template<typename R>
    static string stringifyRegionBody(const R& region)
    {
        string result;
        
        result += "|";

        int i = 1;
        for (const auto& cell : region.cells) {
            result += ' ';
            result += numchar(cell.number);

            if (i++ % 3 == 0)
                result += " |";
        }

        return result;
    }

    string stringify(const Position& position)
    {
        string result;
        
        result = '(';
        result += numchar(position.x);
        result += ", ";
        result += numchar(position.y);
        result += ')';

        return result;
    }

    string stringify(const vector<Position>& positions)
    {
        return join(positions, ", ");
    }

    string stringify(const Cell& cell)
    {
        string result;

        result = '(';
        result += numchar(cell.x());
        result += ", ";
        result += numchar(cell.y());
        result += ": ";
        if (cell.number) {
            result += numchar(cell.number);
        } else {
            result += ".";
        }
        result += ')';

        return result;
    }

    string stringify(const Cells& cells)
    {
        return join(cells, ", ");
    }

    string stringify(const Row& row)
    {
        string result { row.kind() };

        result += " [";
        result += numchar(row.y);
        result += "] ";
        result += stringifyRegionBody(row);

        return result;
    }

    string stringify(const Column& column)
    {
        string result { column.kind() };

        result += " [";
        result += numchar(column.x);
        result += "] ";
        result += stringifyRegionBody(column);

        return result;
    }

    string stringify(const Box& box)
    {
        string result { box.kind() };

        result += " [";
        result += numchar(box.x);
        result += ", ";
        result += numchar(box.y);
        result += "] ";
        result += stringifyRegionBody(box);

        return result;
    }

    string stringify(const Board& board)
    {
        string result;

        const auto firstRow = board.row(1);

        result += "  ";
        for (const auto& cell : firstRow.cells) {
            result += ' ';
            result += numchar(cell.x());
            if (cell.x() % 3 == 0)
                result += "  ";
        }
        result += "\n";

        const char* separator = " +-------+-------+-------\n";
        result += separator;

        const auto column = board.column(1);

        for (const auto& row : board.rows) {
            result += numchar(row.y);
            result += stringifyRegionBody(row);
            result += "\n";

            if (row.y % 3  == 0)
                result += separator;
        }

        return result;
    }

}