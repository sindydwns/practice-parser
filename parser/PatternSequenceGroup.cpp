#include "PatternSequenceGroup.hpp"

PatternSequenceGroup::PatternSequenceGroup() { }
PatternSequenceGroup::PatternSequenceGroup(const PatternSequenceGroup &rhs) { *this = rhs; }
PatternSequenceGroup::~PatternSequenceGroup()
{
    for (size_t i = 0; i < this->patterns.size(); i++) {
        delete this->patterns[i];
    }
}
PatternSequenceGroup &PatternSequenceGroup::operator=(const PatternSequenceGroup &rhs) { (void)rhs; return *this; }

ParseStream::CompileResult PatternSequenceGroup::compile(ParseStream &ps) const
{
    Data *data = dynamic_cast<Data*>(ps.load());
    if (data == NULL) data = new Data();

    std::streampos pos = ps.tellg(); // TODO: 이거 코루틴 구조체에 저장해야 함. 다른 부분도 마찬가지
    if (ps.fail() && ps.isStreamEoF()) return ps.drop(pos, data);
    if (ps.fail()) return ps.yield(data);

    if (this->patterns.size() == 0) return ps.drop(pos, data);
    while (data->searchIdx < this->patterns.size()) {
        ParseStream::CompileResult res = patterns[data->searchIdx]->compile(ps);
        if (res.state == PENDING) return ps.yield(data);
        if (res.state == VALID) {
            data->children.push_back(res.result);
        }
        if (res.state == INVALID) return ps.drop(pos, data);
        data->searchIdx++;
    }
    return ps.done(ParseResult(data->children), data);
}

PatternSequenceGroup *PatternSequenceGroup::addPattern(APattern *pattern)
{
    this->patterns.push_back(pattern);
    return this;
}

PatternSequenceGroup::Data::Data() { }
