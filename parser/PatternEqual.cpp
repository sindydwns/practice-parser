#include "PatternEqual.hpp"
#include <iostream>
PatternEqual::PatternEqual()
    : APattern(true, false) { }
PatternEqual::PatternEqual(const std::string str)
    : APattern(true, false), str(str) { }
PatternEqual::~PatternEqual() {}
PatternEqual::PatternEqual(const PatternEqual &rhs) { *this = rhs; }
PatternEqual &PatternEqual::operator=(const PatternEqual &rhs) { (void)rhs; return *this; }

ParseResult *PatternEqual::parse(std::stringstream &ss) const
{
    std::string buffer(this->str);
    std::streampos pos = ss.tellg();
    ss.seekg(0, ss.end);
    std::streampos end = ss.tellg();
    ss.seekg(pos);
    if (end - pos < static_cast<std::streamoff>(this->str.size())) return NULL;

    char c;
    std::string match;
    while (match.size() < this->str.size()) {
        ss >> c;
        if (ss.fail()) {
            ss.clear();
            ss.seekg(pos);
            return NULL;
        }
        match.push_back(c);
    }
    if (APattern::equal(match, this->str)) {
        if (this->useTrim) return new Result(APattern::trim(buffer));
        return new Result(buffer);
    }
    ss.seekg(pos);
    return NULL;
}

// Result
PatternEqual::Result::Result() { }
PatternEqual::Result::Result(const PatternEqual::Result &rhs) { *this = rhs; }
PatternEqual::Result::Result(std::string match)
    : ParseResult(match) { }
PatternEqual::Result &PatternEqual::Result::operator=(const Result &rhs) { (void)rhs; return *this; }
PatternEqual::Result::~Result() { }
