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

ParseResult *PatternOptionGroup::parse(std::stringstream &ss) const
{
    std::streampos pos = ss.tellg();
    if (pos == std::streampos(-1)) return NULL;

    std::streampos cursor = pos;
    std::vector<ParseResult*> children;
    for (size_t i = 0; i < this->patterns.size();) {
        ParseResult *child = patterns[i]->parse(ss);
        if (child != NULL) {
            children.push_back(child);
            cursor = ss.tellg();
            if (ss.fail()) break;
            i = 0;
        }
        else i++;
        ss.seekg(cursor);
    }
    if (children.size() < minMatch || children.size() > maxMatch) {
        for (size_t i = 0; i < children.size(); i++) {
            delete children[i];
        }
        ss.seekg(pos);
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

std::string PatternOptionGroup::Result::toString() const
{
    std::string res;
    res += "[ ";
    for (size_t i = 0; i < this->children.size(); i++) {
        if (i > 0) res += ", ";
        res += children[i]->toString();
    }
    res += " ]";
    return res;
}
