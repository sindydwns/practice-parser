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
    // TODO delete patterns
}
PatternOptionGroup &PatternOptionGroup::operator=(const PatternOptionGroup &rhs) { (void)rhs; return *this; }

ParseResult *PatternOptionGroup::parse(std::stringstream &ss) const
{
    std::streampos start = ss.tellg();
    std::streampos cursor = start;
    std::vector<ParseResult*> children;
    for (size_t i = 0; i < this->patterns.size();) {
        ParseResult *child = patterns[i]->parse(ss);
        if (child != NULL) {
            cursor = ss.tellg();
            children.push_back(child);
            i = 0;
        }
        else i++;
        ss.seekg(cursor);
    }
    if (children.size() < minMatch || children.size() > maxMatch) {
        for (size_t i = 0; i < children.size(); i++) {
            delete children[i];
        }
        ss.seekg(start);
        return NULL;
    }
    return new Result(children);
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
