#include "PatternReadUntil.hpp"
#include <iostream>

PatternReadUntil::PatternReadUntil()
    : APattern(true, false), useSuffix(false) { throw std::logic_error("must string has value"); }
PatternReadUntil::PatternReadUntil(const std::string str)
    : APattern(true, false), str(str), useSuffix(false)  { if (str.empty()) throw std::logic_error("must string has value"); }
PatternReadUntil::PatternReadUntil(const std::string suffix, const std::string tag)
    : APattern(true, false), str(suffix), useSuffix(false) { setTag(tag); }
PatternReadUntil::PatternReadUntil(const PatternReadUntil &rhs) { *this = rhs; }
PatternReadUntil::~PatternReadUntil() {}
PatternReadUntil &PatternReadUntil::operator=(const PatternReadUntil &rhs) { (void)rhs; return *this; }

ParseStream::CompileResult PatternReadUntil::compile(ParseStream &ps) const
{
    Data *data = dynamic_cast<Data*>(ps.load());
    if (data == NULL) data = new Data();

    std::streampos pos = ps.tellg();
    if (ps.fail() && ps.isStreamEoF()) return ps.drop(pos, data);
    if (ps.fail()) return ps.yield(data);

    char c;
    while (true) {
        ps >> c;
        if (ps.fail() && ps.isStreamEoF()) return ps.drop(pos, data);
        if (ps.fail()) return ps.yield(data);

        data->buffer.push_back(c);

        if (this->str[data->matchIdx] == c) data->matchIdx++;
        else data->matchIdx = 0;

        if (data->matchIdx >= this->str.size()) break;
    }

    if (data->matchIdx < this->str.size()) return ps.drop(pos, data);

    data->buffer = std::string(data->buffer.begin(), data->buffer.end() - this->str.size());
    std::string buffer = APattern::trim(data->buffer, this->useTrim);
    return ps.done(ParseResult(buffer, tag), data);
}

PatternReadUntil *PatternReadUntil::setUseSuffix(bool useSuffix) { this->useSuffix = useSuffix; return this; }

PatternReadUntil::Data::Data() : matchIdx(0) { }
