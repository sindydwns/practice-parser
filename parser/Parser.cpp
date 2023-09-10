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
    ParseResult *res = this->pattern->parse(ss);
    if (ss.eof()) return res;
    delete res;
    return NULL;
}
