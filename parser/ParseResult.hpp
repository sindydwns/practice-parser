#ifndef ParseResult_HPP
#define ParseResult_HPP

#include <iostream>
#include <vector>

class ParseResult
{
public:
    ParseResult();
    ~ParseResult();
    ParseResult(const ParseResult &rhs);
    ParseResult &operator=(const ParseResult &rhs);
};

std::ostream &operator<<(std::ostream &o, ParseResult &res);

#endif
