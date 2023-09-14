#include "PatternEqual.hpp"
#include <iostream>

PatternEqual::PatternEqual()
    : APattern(true, false) { throw std::logic_error("must string has value"); }
PatternEqual::PatternEqual(const std::string str)
    : APattern(true, false), str(str) { if (str.empty()) throw std::logic_error("must string has value"); }
PatternEqual::~PatternEqual() {}
PatternEqual::PatternEqual(const PatternEqual &rhs) { *this = rhs; }
PatternEqual &PatternEqual::operator=(const PatternEqual &rhs) { (void)rhs; return *this; }

ParseStream::CompileResult PatternEqual::compile(ParseStream &ps) const
{
    Data *data = dynamic_cast<Data*>(ps.load());
    if (data == NULL) data = new Data();

    std::streampos pos = ps.tellg();
    if (ps.fail() && ps.isStreamEoF()) return ps.drop(pos, data);
    if (ps.fail()) return ps.yield(data);

    char c;
    while (data->buffer.size() < this->str.size()) {
        ps >> c;
        if (ps.fail() && ps.isStreamEoF()) {
            delete data;
            return ps.drop(pos, data);
        }
        if (ps.fail()) return ps.yield(data);
    }

    if (APattern::equal(data->buffer, this->str)) {
        return ps.done(APattern::trim(data->buffer, this->useTrim), data);
    }
    return ps.drop(pos, data);
}

PatternEqual::Data::Data() { }
