//
// Created by Basuke Suzuki on 5/11/18.
//

#include "parser.h"

namespace sudoku {

    optional<array<int, 9 * 9>> parse(const string& str)
    {
        Parser parser { str };
        return parser.result();
    }

    bool Parser::parse(const string& str)
    {
        size_t count = 0;

        std::copy_if(str.begin(), str.end(), numbers.begin(), [&count, size = numbers.size()](char c) {
            if ((c < '0' || c > '9') && c != '.')
                return false;

            if (count >= size)
                return false;

            count++;
            return true;
        });

        std::transform(numbers.begin(), numbers.end(), numbers.begin(), [](int n) -> int{
            n -= '0';
            return (n < 0 || n > 9) ? 0 : n;
        });

        return true;

    }

    Parser::Parser(const string& str)
    {
        success = parse(str);
    }

    optional<array<int, 9 * 9>> Parser::result() const
    {
        if (success)
            return numbers;
        else
            return nullopt;
    }
}