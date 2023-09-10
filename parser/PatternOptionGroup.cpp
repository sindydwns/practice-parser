#include "PatternOptionGroup.hpp"

PatternOptionGroup::PatternOptionGroup() { }
PatternOptionGroup::PatternOptionGroup(const PatternOptionGroup &rhs) { *this = rhs; }
PatternOptionGroup::~PatternOptionGroup()
{
    // TODO delete patterns
}
PatternOptionGroup &PatternOptionGroup::operator=(const PatternOptionGroup &rhs) { (void)rhs; return *this; }

ParseResult *PatternOptionGroup::parse(std::stringstream &ss) const
{
    std::streampos pos = ss.tellg();
    std::vector<ParseResult*> children;
    for (size_t i = 0; i < this->patterns.size(); i++) {
        ParseResult *child = patterns[i]->parse(ss);
        if (child != NULL) {
            children.push_back(child);
            return new Result(children);
        }
        ss.seekg(pos);
    }
    for (size_t i = 0; i < children.size(); i++) {
        delete children[i];
    }
    ss.seekg(pos);
    return NULL;
}

PatternOptionGroup *PatternOptionGroup::addPattern(APattern *pattern)
{
    this->patterns.push_back(pattern);
    return this;
}


// Result
PatternOptionGroup::Result::Result() { }
PatternOptionGroup::Result::Result(const PatternOptionGroup::Result &rhs) { *this = rhs; }
PatternOptionGroup::Result::Result(std::vector<ParseResult*> children)
    : ParseResult(children) { }
PatternOptionGroup::Result &PatternOptionGroup::Result::operator=(const Result &rhs) { (void)rhs; return *this; }
PatternOptionGroup::Result::~Result() { }
