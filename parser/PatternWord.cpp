#include "PatternWord.hpp"

PatternWord::PatternWord()
    : APattern(true, false) { }
PatternWord::PatternWord(const PatternWord &rhs)
    : APattern(true, false) { *this = rhs; }
PatternWord::~PatternWord() { }
PatternWord &PatternWord::operator=(const PatternWord &rhs)
{
    if (this == &rhs) return *this;
    return *this;
}

ParseResult *PatternWord::parse(std::stringstream &ss) const
{
    if (ss.eof()) return NULL;

    std::streampos pos = ss.tellg();
    std::string ws;
    char c;
    while (true) {
        ss >> c;
        if (ss.fail()) {
            ss.clear();
            ss.seekg(pos);
            return NULL;
        }
        if (std::isspace(c)) ws.push_back(c);
        else {
            ss.unget();
            break;
        }
    }

    std::string str;
    ss >> str;
    if (this->useTrim) return new Result(str);
    return new Result(ws + str);
}

// Result
PatternWord::Result::Result() { }
PatternWord::Result::Result(const PatternWord::Result &rhs) { *this = rhs; }
PatternWord::Result::Result(std::string str)
    : ParseResult(str) { }
PatternWord::Result &PatternWord::Result::operator=(const Result &rhs) { (void)rhs; return *this; }
PatternWord::Result::~Result() { }

