#include "stringify.h"
#include <boost/algorithm/string/join.hpp>

namespace sudoku {

    static char numchar(int c) { return '0' + c; }

    template<typename C>
    static std::string join(const C& items, const std::string& delimiter)
    {
        using T = typename C::value_type;
        std::vector<std::string> itemStrs;

        std::transform(items.begin(), items.end(), std::back_inserter(itemStrs), [](const T& item) {
            return stringify(item);
        });

        auto result = "[" + boost::algorithm::join(itemStrs, delimiter) + "]";
        return result;
    }

    template<typename R>
    static std::string stringifyRegionBody(const R& region)
    {
        std::string result;
        
        result += "|";

        for (const auto& cell : region) {
            result += ' ';
            result += numchar(cell.number);

            if (region.isBorderTiming(cell))
                result += " |";
        }

        return result;
    }

    std::string stringify(const Position& position)
    {
        std::string result;
        
        result = '(';
        result += numchar(position.x);
        result += ", ";
        result += numchar(position.y);
        result += ')';

        return result;
    }

    std::string stringify(const std::vector<Position>& positions)
    {
        return join(positions, ", ");
    }

    std::string stringify(const Cell& cell)
    {
        std::string result;
        
        result = '(';
        result += numchar(cell.x);
        result += ", ";
        result += numchar(cell.y);
        result += ": ";
        if (cell.number) {
            result += numchar(cell.number);
        } else {
            result += ".";
        }
        result += ')';

        return result;
    }

    std::string stringify(const Cells& cells)
    {
        return join(cells, ", ");
    }

    std::string stringify(const Row& row)
    {
        std::string result { row.kind() };
        
        result += " [";
        result += numchar(row.y);
        result += "] ";
        result += stringifyRegionBody(row);

        return result;
    }

    std::string stringify(const Column& column)
    {
        std::string result { column.kind() };
        
        result += " [";
        result += numchar(column.x);
        result += "] ";
        result += stringifyRegionBody(column);

        return result;
    }

    std::string stringify(const Box& box)
    {
        std::string result { box.kind() };
        
        result += " [";
        result += numchar(box.x);
        result += ", ";
        result += numchar(box.y);
        result += "] ";
        result += stringifyRegionBody(box);

        return result;
    }

    std::string stringify(const Board& board)
    {
        std::string result;
        
        const auto row = board.row(1);

        result += "  ";
        for (const auto& cell : row) {
            result += ' ';
            result += numchar(cell.x);
            if (row.isBorderTiming(cell))
                result += "  ";
        }
        result += "\n";

        const char* separator = " +-------+-------+-------\n";
        result += separator;

        const auto column = board.column(1);

        for (const auto& row : board.rows()) {
            result += numchar(row.y);
            result += stringifyRegionBody(row);
            result += "\n";

            if (column.isBorderTiming(row[0]))
                result += separator;
        }

        return result;
    }

}