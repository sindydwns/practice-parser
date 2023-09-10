#include "PatternReadUntil.hpp"
#include <iostream>
PatternReadUntil::PatternReadUntil()
    : APattern("PatternReadUntil", true, false), useStrict(false) { }
PatternReadUntil::PatternReadUntil(const std::string str)
    : APattern("PatternReadUntil", true, false), str(str), useStrict(false)  { }
PatternReadUntil::PatternReadUntil(const PatternReadUntil &rhs)
    : APattern("PatternReadUntil") { *this = rhs; }
PatternReadUntil::~PatternReadUntil() {}
PatternReadUntil &PatternReadUntil::operator=(const PatternReadUntil &rhs) { (void)rhs; return *this; }

bool PatternReadUntil::test(std::stringstream &ss) const
{
    if (this->str.empty()) return this->useStrict == false;
    std::streampos pos = ss.tellg();

    char c;
    std::string res;
    size_t idx = 0;
    while (ss.eof() == false) {
        ss >> c;
        res.push_back(c);
        if (this->str[idx] == c) idx++;
        else idx = 0;
        if (idx >= this->str.size()) return true;
    }

    if (this->useStrict == false) return true;

    ss.seekg(pos);
    return false;
}

PatternReadUntil *PatternReadUntil::setUseStrict(bool useStrict) { this->useStrict = useStrict; return this; }
