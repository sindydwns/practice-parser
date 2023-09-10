#ifndef Parser_HPP
#define Parser_HPP

#include <sstream>
#include "APattern.hpp"
#include "ParseResult.hpp"

class Parser
{
public:
    Parser(const APattern *pattern);
    ~Parser();
    Parser(const Parser &rhs);
    Parser &operator=(const Parser &rhs);

    ParseResult *parse(std::string str) const;

private:
    const APattern *pattern;
    Parser();
};

#endif
