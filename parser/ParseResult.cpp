#include "ParseResult.hpp"

ParseResult::ParseResult() { }
ParseResult::ParseResult(std::string match)
    : match(match) { }
ParseResult::ParseResult(std::vector<ParseResult *> children)
    : children(children) { }
ParseResult::ParseResult(std::string match, std::vector<ParseResult *> children)
    : match(match), children(children) {}
ParseResult::ParseResult(const ParseResult &rhs) { *this = rhs; }
ParseResult::~ParseResult()
{
    for (size_t i = 0; i < this->children.size(); i++) {
        delete this->children[i];
    }
}
ParseResult &ParseResult::operator=(const ParseResult &rhs)
{
    if (this == &rhs) return *this;
    return *this;
}

std::string ParseResult::toString() const { return this->match; }
const std::vector<ParseResult *> &ParseResult::getChildren() const { return this->children; }
