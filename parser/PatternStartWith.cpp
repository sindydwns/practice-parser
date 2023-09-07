#include "PatternStartWith.hpp"
#include <iostream>
PatternStartWith::PatternStartWith() { }
PatternStartWith::PatternStartWith(const std::string str):
    str(str), useTrim(false) { }
PatternStartWith::~PatternStartWith() {}
PatternStartWith::PatternStartWith(const PatternStartWith &rhs) { *this = rhs; }
PatternStartWith &PatternStartWith::operator=(const PatternStartWith &rhs) { (void)rhs; return *this; }

bool PatternStartWith::test(std::stringstream &ss) const
{
    std::string buffer(this->str);
    std::streampos pos = ss.tellg();
    ss.seekg(0, ss.end);
    std::streampos end = ss.tellg();
    ss.seekg(pos);
    if (end - pos < static_cast<std::streamoff>(this->str.size())) {
        return false;
    }

    ss.read(&buffer[0], this->str.size());
    buffer[this->str.size()] = '\0';
    if (buffer == this->str) return true;
    ss.seekg(pos);
    return false;
}

PatternStartWith *PatternStartWith::setUseTrim(bool useTrim) { this->useTrim = useTrim; return this; }
