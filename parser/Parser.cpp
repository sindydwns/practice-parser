#include "Parser.hpp"

Parser::Parser() { }
Parser::~Parser() {}
Parser::Parser(const Parser &rhs)
{
    *this = rhs;
}

Parser &Parser::operator=(const Parser &rhs)
{
    if (this == &rhs) return *this;
    return *this;
}

ParseResult *Parser::parse(std::string str) const
{
    std::stringstream ss(str);
    ss << std::noskipws;
    return NULL;
}
