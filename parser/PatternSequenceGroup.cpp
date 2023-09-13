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

ParseStream::State PatternSequenceGroup::compile(ParseStream &ps) const
{
    return nullptr;
}
ParseResult *PatternSequenceGroup::parse(std::stringstream &ss) const
{
    std::streampos pos = ss.tellg();
    if (pos == std::streampos(-1)) return NULL;
    if (this->patterns.size() == 0) return NULL;

    std::vector<ParseResult*> children;
    for (size_t i = 0; i < this->patterns.size(); i++) {
        ParseResult *child = patterns[i]->parse(ss);
        if (child == NULL) {
            ss.seekg(pos);
            for (size_t k = 0; k < children.size(); k++) {
                delete children[k];
            }
            return NULL;
        }
        children.push_back(child);
    }
    return new Result(children);
}

PatternSequenceGroup *PatternSequenceGroup::addPattern(APattern *pattern)
{
    this->patterns.push_back(pattern);
    return this;
}

// Result
PatternSequenceGroup::Result::Result() { }
PatternSequenceGroup::Result::Result(std::vector<ParseResult*> children)
    : ParseResult(children) { }
PatternSequenceGroup::Result::Result(const PatternSequenceGroup::Result &rhs) { *this = rhs; }
PatternSequenceGroup::Result &PatternSequenceGroup::Result::operator=(const Result &rhs) { (void)rhs; return *this; }
PatternSequenceGroup::Result::~Result() { }

std::string PatternSequenceGroup::Result::toString() const
{
    std::string res;
    res += "{ ";
    for (size_t i = 0; i < this->children.size(); i++) {
        if (i > 0) res += ", ";
        res += children[i]->toString();
    }
    res += "}";
    return res;
}
