#ifndef ParseResult_HPP
#define ParseResult_HPP

#include <exception>
#include <iostream>
#include <vector>

class ParseResult
{
public:
    ParseResult();
    ParseResult(std::string match);
    ParseResult(std::vector<ParseResult> children);
    ParseResult(std::string match, std::vector<ParseResult> children);
    ParseResult(const ParseResult &rhs);
    ~ParseResult();
    ParseResult &operator=(const ParseResult &rhs);

    virtual std::string toString() const;
    const std::vector<ParseResult> &getChildren() const;

private:
    std::string tag;
    std::string match;
    std::vector<ParseResult> children;

};

#endif
