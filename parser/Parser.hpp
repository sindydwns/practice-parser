#ifndef Parser_HPP
#define Parser_HPP

#include <sstream>
#include "ParseResult.hpp"

class Parser
{
public:
    Parser();
    ~Parser();
    Parser(const Parser &rhs);
    Parser &operator=(const Parser &rhs);
    ParseResult *parse(std::string str) const;
private:
};

#endif
