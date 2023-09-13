#include "PatternEqual.hpp"
#include <iostream>
PatternEqual::PatternEqual()
    : APattern(true, false) { }
PatternEqual::PatternEqual(const std::string str)
    : APattern(true, false), str(str) { }
PatternEqual::~PatternEqual() {}
PatternEqual::PatternEqual(const PatternEqual &rhs) { *this = rhs; }
PatternEqual &PatternEqual::operator=(const PatternEqual &rhs) { (void)rhs; return *this; }

ParseStream::State PatternEqual::compile(ParseStream &ps) const
{
    std::string buffer;
    if (ps.yieldStackSize() != 0) buffer = ps.yieldContinue(this);

    std::streampos pos = ps.tellg();
    if (str.empty())                 return ps.yieldReturn(ParseStream::State::VALID, this);
    if (ps.fail() && ps.isUserEoF()) return ps.yieldReturn(ParseStream::State::INVALID, this);
    if (ps.fail())                   return ps.yieldReturn(ParseStream::State::PENDING, buffer, this);

    char c;
    while (buffer.size() < this->str.size()) {
        ps >> c;
        if (ps.fail() && ps.isUserEoF()) return ps.yieldReturn(ParseStream::State::INVALID, this);
        // 리턴하기 전에 ps 상태 clear로 정리해주어야 함.
        // 그렇다면 위에서도 했어야 하는거 아닌가?
    }

    return false;
}
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
