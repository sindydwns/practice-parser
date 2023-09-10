#include "PatternReadUntil.hpp"
#include <iostream>

PatternReadUntil::PatternReadUntil()
    : APattern(true, false), useStrict(false), useSuffix(false) { }
PatternReadUntil::PatternReadUntil(const std::string str)
    : APattern(true, false), str(str), useStrict(false), useSuffix(false)  { }
PatternReadUntil::PatternReadUntil(const PatternReadUntil &rhs) { *this = rhs; }
PatternReadUntil::~PatternReadUntil() {}
PatternReadUntil &PatternReadUntil::operator=(const PatternReadUntil &rhs) { (void)rhs; return *this; }

ParseResult *PatternReadUntil::parse(std::stringstream &ss) const
{
    if (this->str.empty() && this->useStrict) return NULL;
    if (this->str.empty() && this->useStrict == false) return new Result("");
    std::streampos pos = ss.tellg();

    char c;
    size_t idx = 0;
    std::string match;
    while (ss.eof() == false && ss >> c && ss.fail() == false) {
        match.push_back(c);
        if (this->str[idx] == c) idx++;
        else idx = 0;
        if (idx >= this->str.size()) break;
    }

    if (idx >= this->str.size() || this->useStrict == false) {
        std::string::size_type idx = match.rfind(this->str);
        if (idx != std::string::npos) match = std::string(match.begin(), match.begin() + idx);
        if (this->useTrim) return new Result(this->trim(match));
        else return new Result(match);
    }

    ss.seekg(pos);
    return NULL;
}

PatternReadUntil *PatternReadUntil::setUseStrict(bool useStrict) { this->useStrict = useStrict; return this; }
PatternReadUntil *PatternReadUntil::setUseSuffix(bool useSuffix) { this->useSuffix = useSuffix; return this; }

// Result
PatternReadUntil::Result::Result() { }
PatternReadUntil::Result::Result(const PatternReadUntil::Result &rhs) { *this = rhs; }
PatternReadUntil::Result::Result(std::string str)
    : ParseResult(str) { }
PatternReadUntil::Result &PatternReadUntil::Result::operator=(const Result &rhs) { (void)rhs; return *this; }
PatternReadUntil::Result::~Result() { }
