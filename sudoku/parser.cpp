//
// Created by Basuke Suzuki on 5/11/18.
//

#include "parser.h"
#include <string>

namespace sudoku {

    optional<Board> parse(const std::string& str)
    {
        Parser parser { str };
        return parser.result();
    }

    bool Parser::parse(const std::string& str)
    {
        std::array<Number, 81> numbers {};
        size_t count = 0;

        std::copy_if(str.begin(), str.end(), numbers.begin(), [&count, size = numbers.size()](char c) {
            if ((c < '0' || c > '9') && c != '.')
                return false;

            if (count >= size)
                return false;

            count++;
            return true;
        });
        std::transform(numbers.begin(), numbers.end(), numbers.begin(), [](Number n) -> Number {
            n -= '0';
            return (n < 0 || n > 9) ? 0 : n;
        });

        board = Board { numbers };
        return true;

    }

    Parser::Parser(const std::string& str)
    {
        success = parse(str);
    }

    optional<Board> Parser::result() const
    {
        if (success)
            return board;
        else
            return nullopt;
    }
}