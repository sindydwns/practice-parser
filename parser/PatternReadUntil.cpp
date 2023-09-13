#include "PatternReadUntil.hpp"
#include <iostream>

PatternReadUntil::PatternReadUntil()
    : APattern(true, false), useSuffix(false) { }
PatternReadUntil::PatternReadUntil(const std::string str)
    : APattern(true, false), str(str), useSuffix(false)  { }
PatternReadUntil::PatternReadUntil(const PatternReadUntil &rhs) { *this = rhs; }
PatternReadUntil::~PatternReadUntil() {}
PatternReadUntil &PatternReadUntil::operator=(const PatternReadUntil &rhs) { (void)rhs; return *this; }

ParseStream::State PatternReadUntil::compile(ParseStream &ps) const
{
    return false;
}
ParseResult *PatternReadUntil::parse(std::stringstream &ss) const
{
    if (this->str.empty()) return NULL;
    std::streampos pos = ss.tellg();
    if (pos == std::streampos(-1)) return NULL;

    char c;
    size_t idx = 0;
    std::string match;
    while (true) {
        ss >> c;
        if (ss.fail()) {
            ss.clear();
            ss.seekg(pos);
            break;
        }

        match.push_back(c);

        if (this->str[idx] == c) idx++;
        else idx = 0;

        if (idx >= this->str.size()) break;
    }

    if (idx < this->str.size()) {
        ss.seekg(pos);
        return NULL;
    }

    match = std::string(match.begin(), match.end() - this->str.size());
    if (this->useTrim) return new Result(this->trim(match));
    else return new Result(match);
}

PatternReadUntil *PatternReadUntil::setUseSuffix(bool useSuffix) { this->useSuffix = useSuffix; return this; }

// Result
PatternReadUntil::Result::Result() { }
PatternReadUntil::Result::Result(const PatternReadUntil::Result &rhs) { *this = rhs; }
PatternReadUntil::Result::Result(std::string str)
    : ParseResult(str) { }
PatternReadUntil::Result &PatternReadUntil::Result::operator=(const Result &rhs) { (void)rhs; return *this; }
PatternReadUntil::Result::~Result() { }
