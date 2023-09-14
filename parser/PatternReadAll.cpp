#include "PatternReadAll.hpp"

PatternReadAll::PatternReadAll()
    : APattern(false, false) { }
PatternReadAll::PatternReadAll(const PatternReadAll &rhs)
    : APattern(false, false) { *this = rhs; }
PatternReadAll::~PatternReadAll() { }
PatternReadAll &PatternReadAll::operator=(const PatternReadAll &rhs)
{
    if (this == &rhs) return *this;
    return *this;
}

ParseStream::CompileResult PatternReadAll::compile(ParseStream &ps) const
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
    }
    return ps.done(APattern::trim(data->buffer, this->useTrim), data);
}

PatternReadAll::Data::Data() { }
