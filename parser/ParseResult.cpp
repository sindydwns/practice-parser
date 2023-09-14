#include "ParseResult.hpp"

ParseResult::ParseResult() {}
ParseResult::ParseResult(std::string match)
    : match(match) {}
ParseResult::ParseResult(std::string match, const std::string tag)
    : tag(tag), match(match) {}
ParseResult::ParseResult(std::vector<ParseResult> children)
    : children(children) {}
ParseResult::ParseResult(std::vector<ParseResult> children, const std::string tag)
    : tag(tag), children(children) {}
ParseResult::ParseResult(std::string match, std::vector<ParseResult> children)
    : match(match), children(children) {}
ParseResult::ParseResult(std::string match, std::vector<ParseResult> children, const std::string tag)
    : tag(tag), match(match), children(children) {}
ParseResult::ParseResult(const ParseResult &rhs)
    : tag(rhs.tag), match(rhs.match), children(rhs.children) {}
ParseResult::~ParseResult() { }
ParseResult &ParseResult::operator=(const ParseResult &rhs)
{
    if (this == &rhs) return *this;
    this->~ParseResult();
    new (this) ParseResult(rhs);
    return *this;
}

std::string ParseResult::toString() const { return this->match; }
const std::vector<ParseResult> &ParseResult::getChildren() const { return this->children; }
