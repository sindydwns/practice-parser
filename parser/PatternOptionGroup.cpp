#include "PatternOptionGroup.hpp"

PatternOptionGroup::PatternOptionGroup()
    : minMatch(0), maxMatch(1) { }
PatternOptionGroup::PatternOptionGroup(size_t minMatch)
    : minMatch(minMatch), maxMatch(1) { maxMatch = minMatch > maxMatch ? minMatch: maxMatch; }
PatternOptionGroup::PatternOptionGroup(size_t minMatch, size_t maxMatch)
    : minMatch(minMatch), maxMatch(maxMatch) { maxMatch = minMatch > maxMatch ? minMatch: maxMatch; }
PatternOptionGroup::PatternOptionGroup(const PatternOptionGroup &rhs) { *this = rhs; }
PatternOptionGroup::~PatternOptionGroup()
{
    for (size_t i = 0; i < this->patterns.size(); i++) {
        delete this->patterns[i];
    }
}
PatternOptionGroup &PatternOptionGroup::operator=(const PatternOptionGroup &rhs) { (void)rhs; return *this; }

ParseStream::CompileResult PatternOptionGroup::compile(ParseStream &ps) const
{
    Data *data = dynamic_cast<Data*>(ps.load());
    if (data == NULL) data = new Data();

    std::streampos pos = ps.tellg(); // TODO: 이거 코루틴 구조체에 저장해야 함. 다른 부분도 마찬가지
    if (ps.fail() && ps.isStreamEoF()) return ps.drop(pos, data);
    if (ps.fail()) return ps.yield(data);

    if (data->cursor == std::streampos(-1)) data->cursor = pos;
    if (this->patterns.size() == 0) {
        if (this->minMatch == 0) return ps.done(ParseResult(data->children), data);
        return ps.drop(pos, data);
    }
    while (data->searchIdx < this->patterns.size()) {
        ParseStream::CompileResult res = patterns[data->searchIdx]->compile(ps);
        if (res.state == ParseStream::State::PENDING) return ps.yield(data);
        if (res.state == ParseStream::State::VALID) {
            data->children.push_back(res.result);
            data->cursor = ps.tellg();
            data->searchIdx = 0;
        }
        if (res.state == ParseStream::State::VALID_NO_RES) {
            data->cursor = ps.tellg();
            data->searchIdx = 0;
        }
        if (res.state == ParseStream::State::INVALID) {
            data->searchIdx++;
        }
        ps.seekg(data->cursor);
    }
    if (data->children.size() < minMatch || data->children.size() > maxMatch) {
        return ps.drop(pos, data);
    }
    return ps.done(ParseResult(data->children), data);
}

PatternOptionGroup *PatternOptionGroup::addPattern(APattern *pattern)
{
    this->patterns.push_back(pattern);
    return this;
}

PatternOptionGroup::Data::Data() : cursor(std::streampos(-1)), searchIdx(0) { }
