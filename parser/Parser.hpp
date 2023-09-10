#ifndef Parser_HPP
#define Parser_HPP

#include <sstream>
#include "APattern.hpp"
#include "AParseResult.hpp"

class Parser
{
public:
    Parser(const APattern *pattern);
    ~Parser();
    Parser(const Parser &rhs);
    Parser &operator=(const Parser &rhs);

    AParseResult *parse(std::string str) const;

private:
    const APattern *pattern;
    Parser();
};

#endif
