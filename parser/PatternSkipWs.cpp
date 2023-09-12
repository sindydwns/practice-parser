#include "PatternSkipWs.hpp"

PatternSkipWs::PatternSkipWs()
    : APattern(true, false) { }
PatternSkipWs::PatternSkipWs(const PatternSkipWs &rhs)
    : APattern(true, false) { *this = rhs; }
PatternSkipWs::~PatternSkipWs() { }
PatternSkipWs &PatternSkipWs::operator=(const PatternSkipWs &rhs)
{
    if (this == &rhs) return *this;
    return *this;
}

ParseResult *PatternSkipWs::parse(std::stringstream &ss) const
{
    if (ss.eof() == false) ss >> std::ws; 
    return new Result();
}

// Result
PatternSkipWs::Result::Result() { }
PatternSkipWs::Result::Result(const PatternSkipWs::Result &rhs) { *this = rhs; }
PatternSkipWs::Result &PatternSkipWs::Result::operator=(const Result &rhs) { (void)rhs; return *this; }
PatternSkipWs::Result::~Result() { }

