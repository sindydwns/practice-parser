#include "PatternReadUntil.hpp"
#include <iostream>
PatternReadUntil::PatternReadUntil() { }
PatternReadUntil::PatternReadUntil(const std::string str):
    str(str), useTrim(false) { }
PatternReadUntil::~PatternReadUntil() {}
PatternReadUntil::PatternReadUntil(const PatternReadUntil &rhs) { *this = rhs; }
PatternReadUntil &PatternReadUntil::operator=(const PatternReadUntil &rhs) { (void)rhs; return *this; }

bool PatternReadUntil::test(std::stringstream &ss) const
{

    // TODO bug fix

    std::streampos pos = ss.tellg();
    
    if (str.empty()) {
        ss.seekg(0, ss.end);
        return true;
    }

    std::string res;
    std::string buffer("asdfsfda");
    while (ss.eof() == false) {
        std::streampos save = ss.tellg();
        ss >> buffer;
        size_t p = buffer.find(this->str);
        if (p == std::string::npos) {
            res += buffer;
            continue;
        }
        ss.seekg(save);
        ss.seekg(p, ss.cur);
        return true;
    }
    ss.seekg(pos);
    return false;

    // std::streampos pos = ss.tellg();
    
    // if (str.empty()) {
    //     ss.seekg(0, ss.end);
    //     return true;
    // }

    // std::string res;
    // char c;
    // while (ss.eof() == false) {
    //     ss >> c;
    //     res += c;
    //     if (this->str.find(c) != std::string::npos) {
    //         return true;
    //     }
    // }
    // ss.seekg(pos);
    // return false;
}

PatternReadUntil *PatternReadUntil::setUseTrim(bool useTrim) { this->useTrim = useTrim; return this; }
