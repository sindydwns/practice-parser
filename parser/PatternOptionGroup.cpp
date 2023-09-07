#include "PatternOptionGroup.hpp"

PatternOptionGroup::PatternOptionGroup() { }
PatternOptionGroup::~PatternOptionGroup()
{
    // TODO delete patterns
}
PatternOptionGroup::PatternOptionGroup(const PatternOptionGroup &rhs) { *this = rhs; }
PatternOptionGroup &PatternOptionGroup::operator=(const PatternOptionGroup &rhs) { (void)rhs; return *this; }

bool PatternOptionGroup::test(std::stringstream &ss) const
{
    std::streampos pos = ss.tellg();
    for (size_t i = 0; i < this->patterns.size(); i++) {
        if (patterns[i]->test(ss)) {
            ss.seekg(pos);
            return true;
        }
        ss.seekg(pos);
    }
    return false;
}

PatternOptionGroup *PatternOptionGroup::addPattern(APattern *pattern)
{
    this->patterns.push_back(pattern);
    return this;
}
