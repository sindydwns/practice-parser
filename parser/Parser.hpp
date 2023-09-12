#ifndef Parser_HPP
#define Parser_HPP

#include <sstream>
#include "APattern.hpp"
#include "ParseCoroutine.hpp"
#include "ParseResult.hpp"

class Parser
{
public:
    Parser(const APattern *pattern);
    ~Parser();
    Parser(const Parser &rhs);
    Parser &operator=(const Parser &rhs);

    void setPattern(const APattern *pattern);
    ParseCoroutine *makeCoroutine();
    ParseResult *parse(std::string str) const;

private:
    Parser();
    const APattern *pattern;
};

#endif
