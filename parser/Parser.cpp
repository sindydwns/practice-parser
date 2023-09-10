#include "Parser.hpp"

Parser::Parser(): pattern(NULL) { }
Parser::Parser(const APattern *pattern): pattern(pattern) { }
Parser::~Parser()
{
    delete this->pattern;
}
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
    if (pattern == NULL) return NULL;
    std::stringstream ss(str);
    ss << std::noskipws;
    return this->pattern->parse(ss);
}
