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

    ss.read(&buffer[0], this->str.size());
    buffer[this->str.size()] = '\0';
    if (APattern::equal(buffer, this->str)) return new Result(buffer);
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
