#include "PatternReadAll.hpp"

PatternReadAll::PatternReadAll()
    : APattern(false, false) { }
PatternReadAll::PatternReadAll(const PatternReadAll &rhs)
    : APattern(false, false) { *this = rhs; }
PatternReadAll::~PatternReadAll() { }
PatternReadAll &PatternReadAll::operator=(const PatternReadAll &rhs)
{
    if (this == &rhs) return *this;
    return *this;
}

ParseStream::State PatternReadAll::compile(ParseStream &ps) const
{
    return false;
}
ParseResult *PatternReadAll::parse(std::stringstream &ss) const
{
    std::string str;
    char c;
    while (true) {
        ss >> c;
        if (ss.fail()) break;
        str.push_back(c);
    }

    if (this->useTrim) return new Result(APattern::trim(str));
    return new Result(str);
    
}

// Result
PatternReadAll::Result::Result() { }
PatternReadAll::Result::Result(const PatternReadAll::Result &rhs) { *this = rhs; }
PatternReadAll::Result::Result(std::string str)
    : ParseResult(str) { }
PatternReadAll::Result &PatternReadAll::Result::operator=(const Result &rhs) { (void)rhs; return *this; }
PatternReadAll::Result::~Result() { }

