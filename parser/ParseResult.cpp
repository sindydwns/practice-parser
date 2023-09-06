#include "ParseResult.hpp"

ParseResult::ParseResult() { }
ParseResult::~ParseResult() { }
ParseResult::ParseResult(const ParseResult &rhs)
{
    *this = rhs;
}

ParseResult &ParseResult::operator=(const ParseResult &rhs)
{
    if (this == &rhs) return *this;
    return *this;
}

std::ostream &operator<<(std::ostream &o, ParseResult &res)
{
    // TODO
    (void)o;
    (void)res;
    return o;
}
